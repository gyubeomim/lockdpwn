#include "../include/direct.h"

Frame::Frame(cv::Mat src,
             int levels,
             const Intrinsic* ptr_intrinsic,
             int id)
    : images_(Images::for_frame(src, levels)),
      intrinsic_(ptr_intrinsic),
      id_(id)
{
}

Point::Point(Frame* f0,
             const Eigen::Matrix<real,2,1>& uv0,
             const Eigen::Matrix<real,2,1>& n_uv0,
             int patch_size, int id)
    : patch_(Images::for_point(f0->images()->im(), uv0, patch_size)),
      uv0_(uv0),
      node_(new Point3<real>(dynamic_cast<PoseSE3<real>*>(f0->node()), n_uv0, (real)1e-3)),
      f0_(f0),
      id_(id)
{

}

Point::~Point(){
  std::set<OptEdge<real>*> edges = node_->edges();
  for(auto it_e = edges.begin();
      it_e != edges.end();
      it_e++){
    OptEdge<real>* edge = *it_e;
    edge->expire();
    delete edge;
  }
  if(node_->edges().size() > 0){
    printf("Error : expire and remove entire edge before delete point\n");
    exit(1);
  }
  delete patch_;
  delete node_;
}

std::set<DirProjEdge*> track(const std::set<Point*>& visible_points, PoseFrame* frame){
  std::set<DirProjEdge*> prj_edges;
  for(auto it_point = visible_points.begin(); it_point != visible_points.end(); it_point++)
    frame->points().insert(*it_point);
  for(auto it = frame->points().begin(); it != frame->points().end(); it++){
    Point* point = *it;
    DirProjEdge* edge = new DirProjEdge(frame, *it);
    frame->proj_edges()[point] = edge;
    prj_edges.insert(edge);
  }
  return prj_edges;
};

void filter(Frame* frame, int end_level){
  //PoseSE3<real>* pose = dynamic_cast<PoseSE3<real>*>(frame->node());
  Images* images1 = frame->images();
  //cv::MatSize im_size = images1->src().size;
  auto im_size = images1->src().size;
  std::set<Point*> outliers;
  for(auto it_point = frame->points().begin();
      it_point != frame->points().end(); it_point++){
    Point* point = *it_point;
    Point3<real>* pt = point->node();
    Images* patch = point->patch();
    cv::Mat im0 = patch->im().at(end_level);
    const int index_size = patch->index_size(end_level);
    const int patch_size = patch->patch_size(end_level);
    const Eigen::Matrix<real,3,1> Xc = frame->g_cw() * pt->xw();
    const Eigen::Matrix<real,2,1> uv1 = frame->intrinsic()->proj(Xc);
    const ImInfo info0(im0,patch->ix().at(end_level), patch->iy().at(end_level));
    bool outlier = false;
    if(uv1[0] < patch_size ||
       uv1[1] < patch_size ||
       uv1[0] > im_size[1] - patch_size ||
       uv1[1] > im_size[0] - patch_size ){
      outlier = true;
    }
    else{
      real zoom_ratio = zoomout_ratio(Xc, pt->invd());
      cv::Mat im1 = warp(images1->im(), uv1, zoom_ratio, end_level, patch_size);
      const ImInfo info1(im1);
      real outlier_ratio = 0.;
      for(int index = 0; index < index_size; index++){
        real i0, ix, iy, i1;
        bool c0 = info0.get_pixel(index, i0, ix, iy);
        bool c1 = info1.get_pixel(index, i1);
        if(!c0) continue;
        if(!c1) continue;
        real e = i1 - i0;
        if( std::abs(e) > 50.) outlier_ratio += 1.;
      }
      outlier_ratio /= (real) index_size;
      if(outlier_ratio > 0.6) outlier = true;
    }
    if(outlier)
      outliers.insert(point);
  }
  for(auto it_point=outliers.begin();it_point != outliers.end(); it_point++){
    Point* point = *it_point;
    frame->points().erase(point);
    OptEdge<real>* edge = frame->proj_edges().at(point);
    frame->proj_edges().erase(point);
    edge->expire();
    if(frame->node()->edges().count(edge)){
      printf("Error : erase failure\n");
      throw 1;
    }
    delete edge;
  }
  return;
}

DirectMethod::DirectMethod(const Intrinsic* intrinsic) //, real offset)
    :intrinsic_(intrinsic), g_rl_(NULL), n_frame_(0), n_point_(0),
     levels_(5), // feature translation 고려. 회전에서
     patch_size_(16) // 16
{
  // 그림자 코너에서 patch 16, level 5, endlevel 0이 작동됨.
  // level을 높여서 sparse scale에서 회전을 잡고 fine level로 내려가니까 성공
  motion_option_.n_iter = 50; // 50
  motion_option_.intf = &visualizer_;
  motion_option_.motion_update_ratio = 0.5;

  stereo_option_.n_iter = 10; // 10

  bundle_option_.n_iter = 50; // 50
  bundle_option_.motion_update_ratio = 0.2;
  bundle_option_.intf = &visualizer_;
  bundle_option_.marginals = &marginals_;

  // g_rl_.translation() = Eigen::Matrix<real,3,1>(-offset,0., 0.);
  // 임의이 시작점. jacobian 틀린거 없는지 테스트
  // g_cw_latest_.translation() = Eigen::Matrix<real,3,1>(100., 50., -50.);
  // g_cw_latest_.rotX(30./180.*3.141592);
  // g_cw_latest_.rotY(-30./180.*3.141592);
  // g_cw_latest_.rotZ(30./180.*3.141592);
}


// TODO FEJ 다시 적용: Abstract OptEdge에 update외에, pre_update 추가선언
// ===============================================================================================
void DirectMethod::put_image(cv::Mat im0, cv::Mat im1){
  static int count = 0;

  OptNode<real>::set_print_create_destruct(false);
  OptEdge<real>::set_print_create_destruct(false);

  Frame* frame0 = frames_.size()>0 ? frames_.rbegin()->second : NULL;
  Frame* frame = new PoseFrame(im0, levels_, get_g_cw(), intrinsic_, n_frame_);

  frames_[frame->id()] = frame;

  int end_level = 0;

  if(!frame0)
    frame->node()->fix(true);
  else{
    std::set<DirProjEdge*> prj_edges = track(visible_points_, dynamic_cast<PoseFrame*>(frame));
    visualizer_.set_frame(frame);
    // huber cost에 의한 수렴 늦어지는거 감안 필요
    estimate_motion(frame->node(), prj_edges, levels_, end_level, motion_option_);
    filter(frame, end_level);
    visible_points_ = frame->points();
    estimate_bundle(frames_, bundle_option_);
  }

  g_cw_latest_ = frame->g_cw();

  if(is_keyframe(frame)){
    printf("keyframe count %d keyframe %d\n", count, frame->id());
    visualizer_.set_frame(frame);
    if(frame->id() > 0)
      marginalize();
    std::set<Point*> new_points = supply_points(frame);
    visible_points_ = frame->points();
    variable_points_.insert(new_points.begin(),new_points.end());
    stereo_invd(new_points, im1, end_level); // increase im_right_
    n_frame_++;
  }
  else{
    printf("none keyframe\n");
    frames_.erase(frame->id());
    for(auto it_edge = frame->proj_edges().begin();
        it_edge != frame->proj_edges().end();
        it_edge++){
      OptEdge<real>* edge = it_edge->second;
      edge->expire();
      delete edge;
    }
    delete frame;
  }
  count++;
}
// ===============================================================================================

void DirectMethod::marginalize(){
#if 1
  const bool delete_edges = true;
  auto process_mg_points = [this, delete_edges](const std::set<Point*>& mg_points){
                             printf("mg %ld points\n", mg_points.size() );
                             for(auto it_point = mg_points.begin(); it_point != mg_points.end(); it_point++){
                               Point* point = *it_point;
                               Point3<real>* pt = point->node();
                               // proj_edge는 아래 marginalize_point 함수에서 expire된다.
                               marginals_.marginalize_point(pt, delete_edges);
                               variable_points_.erase(point);
                               if(visible_points_.count(point))
                                 visible_points_.erase(point);
                               // frame들이 가지고있는 point의 proj_edge를 찾아가 erase
                               for(int j = point->frame0()->id(); ; j++){
                                 if(j > n_frame_) break;
                                 if(!frames_.count(j)) continue; // 이미 mg된 frame
                                 Frame* f = frames_.at(j);
                                 if(!f->points().count(point)) break;
                                 f->points().erase(point);
                                 f->proj_edges().erase(point);
                               }
                               delete point;  // it includes delete pt, edges of pt
                             }
                           };
  auto search_mg_points = [this](std::set<Point*>& mg_points){
                            for(auto it_point = variable_points_.begin(); it_point != variable_points_.end(); it_point++){
                              Point* point = *it_point;
                              Point3<real>* pt = point->node();
                              if(!visible_points_.count(point))       // mg pt case #1
                                mg_points.insert(point);
                              bool is_stereo = im_right_.count(point->frame0()->id()); // stereo point
                              size_t min_edge = is_stereo ? 1 : 0;
                              if(pt->edges().size() < min_edge){
                                printf("Error : min_edge wrong\n");
                                throw 1;
                              }
                              else if(pt->edges().size() == min_edge) // mg pt case #2
                                mg_points.insert(point);
                            }
                          };
  std::set<Point*> mg_points;
  search_mg_points(mg_points);
  process_mg_points(mg_points);
  std::set<Frame*> mg_frames;
  int n = 0;
  for(auto it = frames_.rbegin(); it != frames_.rend(); it++, n++){
    Frame* f = it->second;
    bool c1 = f->points().size() == 0;
    bool c2 = n >= 3;
    if(c1 || c2)
      mg_frames.insert(f);
  }
  for(auto it_frame = mg_frames.begin(); it_frame != mg_frames.end(); it_frame++){
    Frame* mg_f = *it_frame;
    printf("mg frame[%d]\n", mg_f->id());
    const auto& proj_edges = mg_f->proj_edges();
    for(auto it_edge = proj_edges.begin();
        it_edge != proj_edges.end();
        it_edge++){
      Point* point = it_edge->first;
      Point3<real>* pt = point->node();
      OptEdge<real>* edge = it_edge->second;
      edge->expire();
      delete edge;
    }
    if(!mg_f->node()->fixed())
      marginals_.marginalize_frame(mg_f->node(), delete_edges);
    frames_.erase(mg_f->id()); // frames_ : variable frame만 포함
    mg_f->node()->fix(true);
    fixed_frames_.insert(mg_f);
  }
  mg_points.clear();
  search_mg_points(mg_points);
  process_mg_points(mg_points);
  std::set<const Frame*> f0_frames;
  for(auto it_point = variable_points_.begin(); it_point != variable_points_.end(); it_point++){
    Point* point = *it_point;
    const Frame* f0 = point->frame0();
    f0_frames.insert(f0);
  }
  std::set<Frame*> fixed_frames = fixed_frames_;
  for(auto it_frame = fixed_frames.begin();
      it_frame != fixed_frames.end();
      it_frame++){
    Frame* f = *it_frame;
    if(f0_frames.count(f)) continue; // 아직 필요한 frame
    if(im_right_.count(f->id())){
      Images* im_r = im_right_.at(f->id());
      delete im_r;
      im_right_.erase(f->id());
    }
    printf("delete frame %d\n", f->id());
    fixed_frames_.erase(f);
    delete f;
  }
#else
  int n = 0;
  for(auto it = frames_.rbegin(); it != frames_.rend(); it++, n++){
    if(n < 3) continue;
    it->second->node()->fix(true);
    break;
  }
#endif
}

bool DirectMethod::is_keyframe(Frame* frame) const{
  Eigen::MatrixXi grid(4,1);
  int min_n = 5;
  cv::Size size = frame->images()->src().size();
  float w = (float)size.width / (float)grid.rows();
  float h = (float)size.height / (float)grid.cols();
  grid.setZero();
  for(auto point_it = frame->points().begin();
      point_it != frame->points().end();
      point_it++){
    Point* point = *point_it;
    Eigen::Matrix<real,3,1> Xc = frame->g_cw() * point->node()->xw();
    Eigen::Matrix<real,2,1> x = intrinsic_->proj(Xc);
    int ix = x[0] / w;
    int iy = x[1] / h;
    if(ix < 0 || iy < 0 || ix >= grid.rows() || iy >= grid.cols() )
      continue;
    grid(ix,iy) += 1;
  }
  bool condition = false;
  for(int ix = 0 ; ix < grid.rows(); ix++)
    for(int iy = 0; iy < grid.cols(); iy++)
      if(grid(ix,iy) < min_n ){
        condition = true;
        break;
      }
  return condition;
}

Sophus::SE3<real> DirectMethod::get_g_cw() const{ return g_cw_latest_; }

void estimate_motion(OptNode<real>* pose,
                     const std::set<DirProjEdge*>& prj_edges,
                     int levels,
                     int end_level,
                     const OptimizeBAOption<real>& option){
  if(option.marginals){
    printf("Error : Marginals must be NULL for estimate_motion\n");
    throw 1;
  }
  Visualizer* vis = NULL;
  if(option.intf)
    vis = dynamic_cast<Visualizer*>(option.intf);
  std::set<OptNode<real>*> empty_nodes;
  std::set<OptNode<real>*> pose_nodes = { pose };
  for(int lv = levels-1; lv > end_level-1; lv--){
    for(auto it_e = prj_edges.begin(); it_e != prj_edges.end(); it_e++)
      (*it_e)->set_level(lv);
    if(vis)
      vis->set_level(lv);
    optimize_ba<real>(1, pose_nodes, empty_nodes, option);
  }
}

void estimate_bundle(const std::map<int, Frame*>& frames, const OptimizeBAOption<real>& option){
  std::set<OptNode<real>*> opt_poses;
  std::set<OptNode<real>*> opt_points;
  Visualizer* vis = NULL;
  if(option.intf)
    vis = dynamic_cast<Visualizer*>(option.intf);
  for(auto f_it = frames.begin(); f_it != frames.end(); f_it++){
    const auto& points = f_it->second->points();
    opt_poses.insert(f_it->second->node());
    for(auto point_it = points.begin(); point_it != points.end(); point_it++)
      opt_points.insert((*point_it)->node());
  }
  optimize_ba<real>(1, opt_poses, opt_points, option);
  return;
}

std::set<Point*> DirectMethod::supply_points(Frame* frame){
  Images* images = frame->images();
  cv::Mat src = images->src();
  std::vector<cv::Point2f> corners;
  size_t max_points = 100;
  int max_coners = 100;
  double quality_level = 0.01;
  double min_distance = 40.;
  cv::goodFeaturesToTrack(frame->images()->src(),
                          corners,
                          max_coners,
                          quality_level,
                          min_distance);
  std::set<Point*> new_points;
  for(size_t i=0; i < corners.size(); i++){
    if(frame->points().size() >= max_points) break;
    auto & corner = corners[i];
    Eigen::Matrix<real, 2,1> uv(corner.x, corner.y);
    bool duplicate = false;
    for(auto point_it = frame->points().begin();
        point_it != frame->points().end();
        point_it ++){
      Point3<real>* pt = (*point_it)->node();
      const Eigen::Matrix<real,3,1> Xc = frame->g_cw() * pt->xw();
      const Eigen::Matrix<real,2,1> uv1 = frame->intrinsic()->proj(Xc);
      if((uv1-uv).norm() < min_distance){
        duplicate = true;
        break;
      }
    }
    if(duplicate) continue;
    auto n_uv = intrinsic_->unproj(uv);
    Point* point = new Point(frame, uv, n_uv, patch_size_, n_point_++);
    frame->points().insert(point); // f1 stereo.
    new_points.insert(point);
  }
  return new_points;
}

void DirectMethod::stereo_invd(const std::set<Point*>& new_points, cv::Mat im_right, int end_level){
  if(stereo_option_.marginals){
    printf("Error : Marginals must be NULL for streo_invd\n");
    throw 1;
  }
  Visualizer* vis = NULL;
  if(stereo_option_.intf)
    vis = dynamic_cast<Visualizer*>(stereo_option_.intf);
  Images* images = Images::for_frame(im_right, levels_);
  im_right_[n_frame_] = images;
  std::set<StereoEdge*> stereo_edges;
  std::set<OptNode<real>*> opt_points, empty_nodes;
  for(auto it_point = new_points.begin(); it_point != new_points.end(); it_point++){
    Point* point = *it_point;
    StereoEdge* e = new StereoEdge(point, images, *g_rl_, intrinsic_);
    stereo_edges.insert(e);
    opt_points.insert(point->node());
  }
  for(int lv = levels_-1; lv > end_level-1; lv--){
    for(auto it_e = stereo_edges.begin(); it_e != stereo_edges.end(); it_e++)
      (*it_e)->set_level(lv);
    if(vis)
      vis->set_level(lv);
    optimize_ba<real>(1, empty_nodes, opt_points, stereo_option_);
  }
}

