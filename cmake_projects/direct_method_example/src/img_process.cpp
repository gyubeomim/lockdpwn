#include "../include/direct.h"


cv::Mat pyrup_no_filter(const cv::Mat& im){
  cv::Mat dst;
  if(im.channels() == 1)
    dst = cv::Mat(im.rows*2, im.cols*2, CV_8UC1);
  else
    dst = cv::Mat(im.rows*2, im.cols*2,CV_8UC3);
  for(int i = 0; i<im.rows; i++){
    for(int j= 0; j < im.cols; j++){
      if(im.channels() == 1){
        float v = im.at<unsigned char>(i,j);
        dst.at<unsigned char>(2*i,  2*j) = v;
        dst.at<unsigned char>(2*i+1,2*j) = v;
        dst.at<unsigned char>(2*i,  2*j+1) = v;
        dst.at<unsigned char>(2*i+1,2*j+1) = v;
      }
      else{
        for(size_t k = 0; k < 3; k++){
          float v = im.at<cv::Vec3b>(cv::Point(j,i))[k];
          dst.at<cv::Vec3b>(cv::Point(2*j,   2*i  ))[k] = v;
          dst.at<cv::Vec3b>(cv::Point(2*j+1, 2*i  ))[k] = v;
          dst.at<cv::Vec3b>(cv::Point(2*j,   2*i+1))[k] = v;
          dst.at<cv::Vec3b>(cv::Point(2*j+1, 2*i+1))[k] = v;
        }
      }
    }
  }
  return dst;
}

cv::Mat sub(cv::Mat im1_32f, cv::Mat im0_32f, cv::Scalar color){
  cv::Mat dst(im1_32f.rows, im1_32f.cols, CV_8UC3);
  for(int i =0; i < dst.rows; i++){
    for(int j =0; j < dst.cols; j++){
      float v1 = im1_32f.at<float>(i,j);
      float v0 = im0_32f.at<float>(i,j);

      if(v1 < 0.f || v0 < 0.f){
        for(int k = 0; k <3; k++)
          dst.at<cv::Vec3b>(cv::Point(j,i))[k] = color[k];
      }
      else{
        //unsigned char error = v1 - v0;
        //printf("error = %f\n", v1-v0);
        for(int k = 0; k < 3; k++)
          dst.at<cv::Vec3b>(cv::Point(j,i))[k] = std::round(std::abs(v1-v0));
      }
    }
  }
  return dst;
}


ImInfo::ImInfo(cv::Mat mat_im){
  im_ptr_ = (float*) mat_im.data;
  im_es_ = mat_im.step / sizeof(float);
  ix_ptr_ = NULL;
  iy_ptr_ = NULL;
  ix_es_ = 0;
  hx_ = mat_im.cols/2;
  hy_ = mat_im.rows/2;
  rows_ = mat_im.rows;
  cols_ = mat_im.cols;
}

bool ImInfo::get_pixel(int index, real& i) const {
  if(ix_ptr_){ printf("Error : try to pass ix of point,patch image\n"); throw 1; }
  int u = index / im_es_;
  int v = index % im_es_;
  if(u < 0 || u >= cols_ || v < 0 || v >= rows_){
    i = -1;
    return false;
  }
  i  = im_ptr_[v*im_es_+u];
  if(i < 0) return false;
  return true;
}

ImInfo::ImInfo(cv::Mat mat_im, cv::Mat mat_ix, cv::Mat mat_iy){
  im_ptr_ = (float*) mat_im.data;
  im_es_ = mat_im.step / sizeof(float);
  ix_ptr_ = (float*) mat_ix.data;
  iy_ptr_ = (float*) mat_iy.data;
  ix_es_ = mat_ix.step / sizeof(float);
  hx_ = mat_im.cols/2;
  hy_ = mat_im.rows/2;
  rows_ = mat_im.rows;
  cols_ = mat_im.cols;
}

bool ImInfo::get_pixel(int index, real& i, real& ix, real&iy) const {
  if(!ix_ptr_){ printf("Error : try to acces ix of frame image\n"); throw 1; }
  // dv*warped_im_es+du
  int u = index / im_es_;
  int v = index % im_es_;
  const int gi_idx = v*ix_es_+u;
  if(u < 0 || u >= cols_ || v < 0 || v >= rows_){
    i = -1;
    ix = 0;
    iy = 0;
    return false;
  }
  i  = im_ptr_[v*im_es_+u];
  ix = ix_ptr_[gi_idx];
  iy = iy_ptr_[gi_idx];
  if( i < 0){
    ix = 0;
    iy = 0;
    return false;
  }
  return true;
}

Eigen::Matrix<int,2,1> ImInfo::get_dxy(int index) const{
  Eigen::Matrix<int,2,1> dxy;
  int u = index / im_es_;
  int v = index % im_es_;
  dxy[0] = u - hx_;
  dxy[1] = v - hy_;
  return dxy;
}


cv::Mat warp(const std::vector<cv::Mat>&vim,
             const Eigen::Matrix<real,2,1>& x, // on level 0
             real zoom_out_ratio, int lv0,
             size_t patch_size){
  cv::Mat dst(patch_size, patch_size, CV_32F);
  size_t dst_es = dst.step / sizeof(float);
  //patch_scale = std::round(patch_scale);
  // scale을 먼저 맞춰야함
  if(dst.cols%2==1){
    printf("Error : odd patch_size\n");
    throw 1;
  }
  if(dst.rows%2==1){
    printf("Error : odd patch_size\n");
    throw 1;
  }
  cv::Mat im;
#if 0
  level_scale = std::pow(0.5,level);
  im = vim.at(level);
#else
  int level = lv0;
  real level_scale = std::pow(0.5, level);
  im = vim.at(level);
  while(true){
    if(level+1 >= vim.size()) break;
    if(zoom_out_ratio < 2.) break;
    level++;
    im = vim.at(level);
    level_scale *= 0.5;
    zoom_out_ratio *= 0.5;
  }
#endif
  real hw = zoom_out_ratio * (real)dst.cols / 2.f;
  real hh = zoom_out_ratio * (real)dst.rows / 2.f;
  real x1 = level_scale*x[0] + hw - 1.f;
  real y1 = level_scale*x[1] + hh - 1.f;
  real x0 = level_scale*x[0] - hw;
  real y0 = level_scale*x[1] - hh;
  size_t im_es = im.step / sizeof(float);
  real ustep = (x1-x0+1.f)/(real)(dst.cols);
  real vstep = (y1-y0+1.f)/(real)(dst.rows);
  //printf("sacle, u, x0, x1, ustep = %f, %f, %f, %f, %f\n", scale, x[0],  x0, x1, ustep);
  //printf("-------------------\n");
  for(int iv = 0; iv < dst.rows; iv++){
    for(int iu = 0; iu < dst.cols; iu++){
      float* output = ((float*)dst.data) + (iv*dst_es + iu);
      real u = x0+(real)iu*ustep;
      real v = y0+(real)iv*vstep;
      //printf("u,v = %f,%f\n", u, v);
      int ref_iu = floorf(u);
      int ref_iv = floorf(v);
      if(ref_iu < 0 || ref_iv < 0 || ref_iu+1 >= im.cols || ref_iv+1 >= im.rows){
        *output = -1.;
        continue;
      }
      float* ref = ((float*)im.data) + (ref_iv*im_es + ref_iu);
      real subpix_u = u - (real)ref_iu;
      real subpix_v = v - (real)ref_iv;
      real w_tl = (1. - subpix_u) * (1. - subpix_v);
      real w_tr = subpix_u * (1. - subpix_v);
      real w_bl = (1. - subpix_u) * subpix_v;
      real w_br = subpix_u * subpix_v;
      *output = w_tl * ref[0]
                + w_tr * ref[1]
                + w_bl * ref[im_es]
                + w_br * ref[im_es+1];
      //if(false){
      //    printf("ref_u,v = %f, %f\n", u, v);
      //    printf("ref_iu,v = %d, %d\n", ref_iu, ref_iv);
      //}
    }
  }
  return dst;
}


void gradient(const cv::Mat& im, cv::Mat& ix, cv::Mat& iy){
  ix = cv::Mat(im.rows, im.cols, CV_32F);
  iy = cv::Mat(im.rows, im.cols, CV_32F);
  const float* im_ptr = (float*) im.data;
  float* ix_ptr = (float*) ix.data;
  float* iy_ptr = (float*) iy.data;
  //printf("gradient %d, %d\n", im.cols, im.rows);
  size_t im_es = im.step / sizeof(float);
  size_t i_es = ix.step / sizeof(float);
  for(int iv = 0; iv < im.rows; iv++){
    for(int iu = 0; iu < im.cols; iu++){
      const size_t im_idx0 = iv*im_es + iu;
      const size_t i_idx0 = iv*i_es + iu;
      //float val = im_ptr[im_idx0];
      float val = -1.;
      if(iu+1 >= im.cols)
        val = im_ptr[im_idx0] - im_ptr[iv*im_es+iu-1];
      else if(iu < 1)
        val = im_ptr[iv*im_es+iu+1]-im_ptr[im_idx0];
      else
        val = (im_ptr[iv*im_es+iu+1] - im_ptr[iv*im_es+iu-1])/2.;
      ix_ptr[i_idx0] = val;
      val = -1.;
      if(iv+1 >= im.rows)
        val = im_ptr[im_idx0] - im_ptr[(iv-1)*im_es+iu];
      else if(iv < 1)
        val = im_ptr[(iv+1)*im_es+iu] - im_ptr[im_idx0];
      else
        val = (im_ptr[(iv+1)*im_es+iu] - im_ptr[(iv-1)*im_es+iu])/2.;
      iy_ptr[i_idx0] = val;
    }
  }
}

cv::Mat cvt_8UC1(cv::Mat src){
  cv::Mat dst;
  src.convertTo(dst, CV_8UC1);
  return dst;
}

Images::Images(cv::Mat src, int levels)
    : src_(src.clone())
{
  im_.reserve(levels);
  cv::Mat curr_im;
  src_.convertTo(curr_im, CV_32F);
  im_.push_back(curr_im);

  for(int level=1; level < levels; level++){
    cv::pyrDown(curr_im, curr_im);
    im_.push_back(curr_im);
  }
}

Images::Images(const std::vector<cv::Mat>& vim, const Eigen::Matrix<real,2,1>& uv, size_t patch_size) {
  im_.reserve(vim.size());
  ix_.reserve(vim.size());
  iy_.reserve(vim.size());
  for(size_t lv = 0; lv < vim.size(); lv++){
    cv::Mat im = warp(vim, uv, 1., lv, patch_size);
    im_.push_back(im);
    cv::Mat ix, iy;
    gradient(im, ix, iy);
    ix_.push_back(ix);
    iy_.push_back(iy);
  }
}

void Visualizer::on_update(const OptInfo<real>& info)
{
  static int g_iter = 0;

  /*if(info.ri_->size() > 0 && info.rj_->size() > 0){
    printf("iter l/g %2ld/%4d, ", info.iter_, g_iter);
    printf("n(rj), n(ri), n, m = %2ld, %3ld, %3ld, %3ld",
    info.rj_->size(), info.ri_->size(),info.Ha_->rows(),
    info.Hb_->cols());
    printf(" / from / n(fp), n(p) = %ld, %ld\n", info.fp_edges_->size(), info.p_edges_->size());
    printf("n(prj_edge) = %ld\n", frame_->proj_edges().size());
    }
    else if (info.rj_->size() == 1){
    printf("iter l/g %2ld/%4d, ", info.iter_, g_iter);
    printf("motion estimation\n");
    }
    printf("iter, chi2 = %3ld, %4.2f\n", info.iter, info.chi2); */

  real scale = std::pow(0.5, (real)lv_);
  Images* images = frame_->images();

  cv::Mat im = images->src().clone();
  cv::cvtColor(im, im, cv::COLOR_GRAY2RGB);

  if(feature_criteria_)
    im = feature_criteria_->draw_mask(im);
  else{
    //printf("TODO : null feature_criteria_\n");
  }

  PoseSE3<real>* pose = dynamic_cast<PoseSE3<real>*>(frame_->node());
  std::map<int, Point*> points;

  size_t patch_size = 10;

  for(auto it_point = frame_->points().begin(); it_point != frame_->points().end(); it_point++)
  {
    Point* point = (*it_point);
    points[point->id()] = point;

    Images* patch = point->patch();
    patch_size = patch->patch_size(lv_);
  }

  const size_t n_patch_cols = 40;
  const size_t n_patch_rows = 3;
  const size_t dst_pyrup_times = 1;

  cv::Mat dst_patches = cv::Mat(
      std::pow(2,dst_pyrup_times) * 3 * n_patch_rows * patch_size,
      std::pow(2,dst_pyrup_times) * n_patch_cols * patch_size,
      CV_8UC3);

  dst_patches.setTo(0);

  size_t pt_n =0;

  for(auto it = points.begin(); it != points.end(); it++)
  {
    Point* point = it->second;
    Point3<real>* pt = point->node();
    std::stringstream str_id;

    str_id << boost::format("%ld") % point->id();

    Images* patch = point->patch();

    Eigen::Matrix<real,3,1> Xc = pose->g_cw() * pt->xw();
    Eigen::Matrix<real,2,1> uv1 = frame_->intrinsic()->proj(Xc);

    cv::Mat im0 = patch->im().at(lv_);
    real ratio = zoomout_ratio(Xc, pt->invd());
    cv::Mat im1 = warp(images->im(), uv1, ratio, lv_, patch_size);

    const ImInfo info0(im0,patch->ix().at(lv_), patch->iy().at(lv_));
    const ImInfo info1(im1);

    // comment(edward): dx, dy are depending on scale.
    real dx = info0.hx_ / scale;
    real dy = info0.hy_ / scale;

    cv::Point2f hb(dx, dy);
    cv::Point2f cv_uv( uv1.x(), uv1.y());

    // comment(edward): green rectangle
    cv::rectangle(im, cv_uv-hb, cv_uv+hb, cv::Scalar(0,255,0), 1);
    // comment(edward): blue rectangle
    cv::rectangle(im, cv_uv-ratio*hb, cv_uv+ratio*hb, cv::Scalar(255,0,0), 1);

    std::stringstream str_rho;

    str_rho << boost::format("%.4f") % pt->invd();

    cv::putText(im, str_id.str(), cv_uv+cv::Point2f(10.,10.),
                cv::FONT_HERSHEY_PLAIN, 1., cv::Scalar(255, 0), 1);
    cv::putText(im, str_rho.str(), cv_uv+cv::Point2f(10.,20.),
                cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(255, 0), 1);

    if(pt_n >= n_patch_cols*n_patch_rows) continue;

    cv::Mat dst_im0 = cvt_8UC1(im0);
    cv::Mat dst_im1 = cvt_8UC1(im1);

    cv::Mat patch_3by1(3*patch_size,patch_size, CV_8UC1);

    cv::Rect roi1(0,           0,patch_size, patch_size);
    cv::Rect roi2(0,1*patch_size,patch_size, patch_size);
    cv::Rect roi3(0,2*patch_size,patch_size, patch_size);

    patch_3by1.setTo(0);

    dst_im0.copyTo(patch_3by1(roi1));
    dst_im1.copyTo(patch_3by1(roi2));

    cv::cvtColor(patch_3by1, patch_3by1, cv::COLOR_GRAY2RGB);
    cv::Mat dst_error = sub(im0, im1, cv::Scalar(100,50,50));

    dst_error.copyTo(patch_3by1(roi3));

    for(size_t n=0; n<dst_pyrup_times;n++)
      patch_3by1 = pyrup_no_filter(patch_3by1);

    size_t row = (pt_n/n_patch_cols);
    size_t col = pt_n % n_patch_cols;

    cv::Rect roi_row( col * patch_3by1.cols,
                      row *patch_3by1.rows,
                      patch_3by1.cols,
                      patch_3by1.rows);

    cv::putText(patch_3by1, str_id.str(), cv::Point2f(2.,10.), cv::FONT_HERSHEY_PLAIN, 0.6, cv::Scalar(255,0,0), 1);

    std::stringstream str_pos;

    str_pos << boost::format("%.f,%.f") % uv1.x() % uv1.y() ;

    cv::putText(patch_3by1, str_pos.str(), cv::Point2f(2.,25.), cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(0,0,255), 1);

    patch_3by1.copyTo(dst_patches(roi_row));
    pt_n ++;
  }

  const auto t = pose->g_cw().inverse().translation();
  const auto quat = pose->g_cw().inverse().unit_quaternion();

  std::stringstream ss;
  ss << boost::format("frame[%d] tf_wc(quat, t) = %.3f, %.3f, %.3f, %.3f, %.3f, %.3f")
      % frame_->id() % quat.x() % quat.y() % quat.z() % t.x() % t.y() % t.z();

  //cv::rectangle(im, cv::Point(0,0), cv::Point(800., 25.), cv::Scalar(255,255,255), -1);

  cv::putText(im, ss.str(), cv::Point(15,15), cv::FONT_HERSHEY_PLAIN,
              1.0, CV_RGB(0, 0, 255), 1);

  cv::Mat dst(im.rows+dst_patches.rows, std::max(im.cols, dst_patches.cols), CV_8UC3);

  dst.setTo(0);
  im.copyTo(dst(cv::Rect(0,0,im.cols,im.rows)));
  dst_patches.copyTo(dst(cv::Rect(0,im.rows,dst_patches.cols,dst_patches.rows)));

  cv::imshow("direct method", dst);

  if(g_iter==0)
    cv::moveWindow("direct method", 100, 300);

  g_iter ++;

  if(info.error_)
    set_stop(true);

  char c = cv::waitKey(stopmode_?0:1);

  if(c == 'q') exit(1);
  else if(c == 's') stopmode_ = !stopmode_;
}

void zoomout_test(cv::Mat im0)
{
  int levels = 5;

  Sophus::SE3<real> g0;
  Eigen::Matrix<real,3,3> K = Eigen::Matrix<real,3,3>::Identity();

  Intrinsic* intrinsic = new RadTanIntrinsic(K, Eigen::Matrix<real,4,1>(0.,0.,0.,0.));
  Frame* f0 = new PoseFrame(im0, levels, g0, intrinsic, 0);

  std::vector<cv::Point2f> corners;

  int max_coners = 100;
  double quality_level = 0.01;
  double min_distance = 10.;

  cv::goodFeaturesToTrack(f0->images()->src(),
                          corners,
                          max_coners,
                          quality_level,
                          min_distance);
  auto & corner = corners.at(0);
  Eigen::Matrix<real,2,1> uv = Eigen::Matrix<real,2,1>(corner.x, corner.y);
  std::cout << "corner at " << uv.transpose() << std::endl;
  std::cout << "z/x for zoom out/in" << std::endl;
  int lv = 0;
  real zoom_out_ratio = 1.f;
  size_t patch_size = 20;
  char c = 0;
  {
    cv::Mat patch = warp(f0->images()->im(), uv, zoom_out_ratio, lv, patch_size);
    cv::Mat dst = cvt_8UC1(patch);
    for(int i = 0; i < 4; i++) dst = pyrup_no_filter(dst);
    cv::imshow("dst0", dst);
    cv::moveWindow("dst0", 100,100);
  }

  int k =0;
  while(c != 'q'){
    cv::Mat patch = warp(f0->images()->im(), uv, zoom_out_ratio, lv, patch_size);
    cv::Mat dst = cvt_8UC1(patch);
    for(int i = 0; i < 4; i++) dst = pyrup_no_filter(dst);
    cv::imshow("src", im0);
    cv::imshow("dst", dst);
    if(++k==0){
      cv::moveWindow("dst", 100,100);
      cv::moveWindow("src", 100,100);
    }
    c = cv::waitKey(0);
    if(c=='z'){
      zoom_out_ratio *= 1.01;
      printf("zoom_out_ratio = %f\n", zoom_out_ratio);
    }
    else if(c=='x'){
      zoom_out_ratio /= 1.01;
      printf("zoom_out_ratio = %f\n", zoom_out_ratio);
    }
  }
  return;
}

