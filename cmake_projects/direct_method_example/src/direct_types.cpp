#include "../include/direct.h"

StereoEdge::StereoEdge(Point* point,
        const Images* images1,
        const Sophus::SE3<real>& g_c0,
        const Intrinsic* intrinsic
        ) :
    point_(point),
    images1_(images1),
    g_c0_(g_c0),
    intrinsic_(intrinsic),
    lv_(0)
{
    OptNode<real>* pt = point->node();
    OptEdge<real>::nodes().push_back(pt);
    pt->addEdge(this);
    Eigen::Matrix<real,1,1> jb;
    hessians_.push_back(jb.transpose()*jb);
    hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(pt,pt));
    jres_.push_back(Eigen::Matrix<real,1,1>());
}

void StereoEdge::update(){
    real scale = std::pow(0.5, (real)lv_);
    Point3<real>* pt = point_->node();
    const real rho = pt->invd(); // pt update에서 limit
    // TODO FEJ 적용하면 중복계산 줄어들 부분
    const int index_size = point_->patch()->index_size(lv_);
    const int patch_size = point_->patch()->patch_size(lv_);
    const Images* patch = point_->patch();
    const auto& n_uv0 = point_->n_uv0();
    const auto X0 = pt->x0();
    const auto Xc = g_c0_ * X0;
    Eigen::Matrix<real,2,3> dpibar_dXc; {
        real v = 1. / Xc[2];
        real v2 = v*v;
        dpibar_dXc << v, 0., -Xc[0]*v2,
                   0., v, -Xc[1]*v2;
        // TODO : distortion ignored.
    }
    Eigen::Matrix<real,2,3> dpi_dXc = intrinsic_->K().block<2,2>(0,0) * dpibar_dXc; // dpi_drho
    const Eigen::Matrix<real,3,3>& dXc_dX0 = g_c0_.rotationMatrix();
    Eigen::Matrix<real,3,1> dX0_drho; {
        real v = 1. / rho / rho;
        dX0_drho << - n_uv0[0]*v, -n_uv0[1]*v, -v;
    }
    Eigen::Matrix<real,2,1> dspi_drho = scale * dpi_dXc * dXc_dX0 * dX0_drho;
#if 1
    // cam0의 uv에서 dx만큼 움직이면, cam의 uv proj에서 dpi가 dpi_dx.
    // 주의 : 좌우 intrinsic이 같은 rectified stereo 가정하에서만 구현된 edge
    Eigen::Matrix<real, 2,2> dpi_dx
        = dpi_dXc * dXc_dX0.block<3,2>(0,0) * X0[2] * intrinsic_->K().block<2,2>(0,0).inverse();
#else
    // 에서 K1 * K0.inverse() 소거한게 아래식.
    Eigen::Matrix<real,2,2> dpi_dx = dpibar_dXc * X0[2] * g_c0_.rotationMatrix().block<3,2>(0,0);
#endif
    Eigen::Matrix<real,2,1> uv1 = intrinsic_->proj(Xc);
    real ratio = zoomout_ratio(Xc, rho);
    cv::Mat im1 = warp(images1_->im(), uv1, ratio, lv_, patch_size);
    const ImInfo info0( patch->im().at(lv_), patch->ix().at(lv_), patch->iy().at(lv_) );
    const ImInfo info1( im1 );
    hessians_[0].setZero();
    jres_[0].setZero();
    error_.setZero();
    for(int index = 0; index < index_size; index++){
        real i0, ix, iy, i1;
        bool c0 = info0.get_pixel(index, i0, ix, iy);
        bool c1 = info1.get_pixel(index, i1);
        if(!c0) continue;
        if(!c1) continue;
        Eigen::Matrix<real, 1,1> err(i0 - i1);
        Eigen::Matrix<real, 1,2> gI0(ix,iy);
        Eigen::Matrix<real, 1,1> J = - gI0 * dpi_dx.inverse() * dspi_drho;
        real W = huber(err(0), 30.);
        hessians_[0] += W * J.transpose() * J;
        jres_[0]     += W * J.transpose() * err;
        error_       += err;
    }
    return;
}

DirProjEdge::DirProjEdge(PoseFrame* frame, Point* point)
: frame_(frame),
point_(point),
lv_(-1) {
    if(frame_ == point->frame0()){
        printf("Error : frame can't be pose0\n");
        throw 1;
    }
    OptNode<real>* f = frame->node();
    OptNode<real>* pt = point->node();
    OptEdge<real>::nodes().push_back(f);
    OptEdge<real>::nodes().push_back(pt);
    f->addEdge(this);
    pt->addEdge(this);
    Eigen::Matrix<real,1,6> ja;
    Eigen::Matrix<real,1,1> jb;
    hessians_.push_back(ja.transpose()*ja);
    hessians_.push_back(jb.transpose()*jb);
    hessians_.push_back(ja.transpose()*jb);
    hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, f));
    hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(pt, pt));
    hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, pt));
    jres_.push_back(Eigen::Matrix<real,6,1>());
    jres_.push_back(Eigen::Matrix<real,1,1>());
}

void DirProjEdge::update(){
    Point3<real>* pt = point_->node();
    PoseSE3<real>* pose = dynamic_cast<PoseSE3<real>*>(frame_->node());
    const real rho = pt->invd(); // pt update에서 limit
    const auto& n_uv0 = point_->n_uv0();
    const auto& g_0w = pt->frame0()->g_cw();
    const auto g_c0 = pose->g_cw() * g_0w.inverse(); // !<< missing inverse
    const auto X0 = pt->x0();
    const auto Xc = g_c0 * X0;
    const auto Xw = g_0w.inverse() * X0;
    const auto& K = frame_->intrinsic()->K();
    const Eigen::Matrix<real,2,1> uv1 = frame_->intrinsic()->proj(Xc);
    // ja
    Eigen::Matrix<real,2,6> dpi0_dxi;{
        Eigen::Matrix<real,2,3> dpi0_dX0; {
            real v2 = rho * rho;
            dpi0_dX0 << rho, 0., -X0[0]*v2,
                        0., rho, -X0[1]*v2;
            dpi0_dX0 = K.block<2,2>(0,0)*dpi0_dX0;
        }
        Eigen::Matrix<real,3,6> dXw_dxi;{ // d  e^(xi)Xw d xi
            dXw_dxi.block<3,3>(0,0).setIdentity();
            dXw_dxi.block<3,3>(0,3) = - skew(Xw);
        }
        dpi0_dxi = dpi0_dX0 * g_0w.rotationMatrix() * dXw_dxi;
    }
    // jb
    Eigen::Matrix<real,2,1> dpi0_drho; {
        Eigen::Matrix<real,3,1> dX0_drho;{
            real v = 1. / rho / rho;
            dX0_drho << - n_uv0[0]*v, -n_uv0[1]*v, -v;
        }
        Eigen::Matrix<real,2,3> dpibar_dXc; {
            real v = 1./Xc[2];
            real v2 = v*v;
            dpibar_dXc << v, 0., -Xc[0]*v2,
                          0., v, -Xc[1]*v2;
        }
        Eigen::Matrix<real,2,3> dpi_dXc = K.block<2,2>(0,0)*dpibar_dXc;
        const Eigen::Matrix<real,3,3>& dXc_dX0 = g_c0.rotationMatrix();
        Eigen::Matrix<real, 2,1> dpi_drho = dpi_dXc * dXc_dX0 * dX0_drho;
#if 1
        // cam0의 uv에서 dx만큼 움직이면, cam의 uv proj에서 dpi가 dpi_dx.
        Eigen::Matrix<real, 2,2> dpi_dx
            = dpi_dXc * dXc_dX0.block<3,2>(0,0) * X0[2] * K.block<2,2>(0,0).inverse();
#else
        // 에서 K1 * K0.inverse() 소거한게 아래식.
        Eigen::Matrix<real, 2,2> dpi_dx = dpibar_dXc * X0[2] * g_c0.rotationMatrix().block<3,2>(0,0);
#endif
        dpi0_drho =  - dpi_dx.inverse()* dpi_drho;
    }
    real scale = std::pow(0.5, (real)lv_);
    const int index_size = point_->patch()->index_size(lv_); // 1열로 풀어넣은것?
    const int patch_size = point_->patch()->patch_size(lv_); // index_size의 sqrt?
    const Images* patch = point_->patch();
    real ratio = zoomout_ratio(Xc, rho);
    cv::Mat im1 = warp(frame_->images()->im(), uv1, ratio, lv_, patch_size);
    const ImInfo info0( patch->im().at(lv_), patch->ix().at(lv_), patch->iy().at(lv_) );
    const ImInfo info1( im1 );
    for(size_t i = 0; i < hessians_.size(); i++) hessians_[i].setZero();
    for(size_t i = 0; i < jres_.size(); i++)     jres_[i].setZero();
    error_.setZero();

    for(int index = 0; index < index_size; index++){
        real i0, ix, iy, i1;
        bool c0 = info0.get_pixel(index, i0, ix, iy);
        bool c1 = info1.get_pixel(index, i1);
        if(!c0) continue;
        if(!c1) continue;
        Eigen::Matrix<real,1,1> err(i0-i1);
        Eigen::Matrix<real,1,2> gI0(ix,iy);
        const Eigen::Matrix<real,1,6> ja = scale*gI0*dpi0_dxi;
        const Eigen::Matrix<real,1,1> jb = scale*gI0*dpi0_drho;
        real W = huber(err(0), 30.);
        hessians_[0] += W * ja.transpose()*ja;
        hessians_[1] += W * jb.transpose()*jb;
        hessians_[2] += W * ja.transpose()*jb;
        jres_[0]     += W * ja.transpose()*err;
        jres_[1]     += W * jb.transpose()*err;
        error_       += err;
    }
    return;
}

void motion_invd_test(cv::Mat im0, cv::Mat im1, const Intrinsic* intrinsic, float offsetf, TestCase test_case){
    int levels = 5;
    int patch_size = 16;
    Sophus::SE3<real> g0;
    Sophus::SE3<real> g1;
    g1.translation() = Eigen::Matrix<real,3,1>(-offsetf,0.,0.);
    Frame* f0 = new PoseFrame(im0, levels, g0, intrinsic, 0);
    Frame* f1 = new PoseFrame(im1, levels, g1, intrinsic, 1);
    f0->node()->fix(true);
    Eigen::Matrix<real,2,1> uv;
    std::set<OptNode<real>*> opt_points;
    std::set<StereoEdge*> stereo_edges;
    {    // supply_point
        std::vector<cv::Point2f> corners;
        int max_coners = 100;
        double quality_level = 0.01;
        double min_distance = 100.;
        cv::goodFeaturesToTrack(f0->images()->src(),
                corners,
                max_coners,
                quality_level,
                min_distance);
        for(size_t i=0; i < corners.size(); i++){
            auto & corner = corners[i];
            Eigen::Matrix<real, 2,1> uv(corner.x, corner.y);
            auto n_uv = intrinsic->unproj(uv);
            Point* point = new Point(f0, uv, n_uv, patch_size, i);
            f0->points().insert(point);
            f1->points().insert(point); // f1 stereo.
            StereoEdge* e = new StereoEdge(point, f1->images(), g1, intrinsic);
            opt_points.insert(point->node());
            stereo_edges.insert(e);
        }
    }
    Visualizer visualizer;
    size_t point_dim = 1;
    OptimizeBAOption<real> option;
    option.intf = &visualizer;
    option.n_iter = 20;

    // Depth estimation for keyframe
    for(int lv = levels-1; lv > -1; lv--){
        std::set<OptNode<real>*> empty_nodes;
        for(auto it_e = stereo_edges.begin(); it_e != stereo_edges.end(); it_e++)
            (*it_e)->set_level(lv);
        visualizer.set_frame(f1);
        visualizer.set_level(lv);
        optimize_ba<real>(point_dim, empty_nodes, opt_points, option);
    }
    if(test_case == INVD_TEST) return;
    // Adding projection edge
    std::set<DirProjEdge*> proj_edges;
    for(auto it_point = f0->points().begin(); it_point != f0->points().end(); it_point++){
        Point* point = *it_point;
        if(point->frame0() == f1) continue;
        DirProjEdge* e = new DirProjEdge(dynamic_cast<PoseFrame*>(f1), point);
        proj_edges.insert(e);
    }
    std::set<OptNode<real>*> opt_poses = {f1->node(), };
    // Motion estimation
    for(int lv = levels-1; lv > -1; lv--){
        std::set<OptNode<real>*> empty_nodes;
        for(auto it_e = proj_edges.begin(); it_e != proj_edges.end(); it_e++)
            (*it_e)->set_level(lv);
        visualizer.set_frame(f1);
        visualizer.set_level(lv);
        optimize_ba<real>(point_dim, opt_poses, empty_nodes, option);
    }

    PoseSE3<real>* pose = dynamic_cast<PoseSE3<real>*>(f1->node());
    std::cout << "g_cw from motion estimation = \n" << pose->g_cw().matrix3x4() << std::endl;
    // BA
    optimize_ba<real>(point_dim, opt_poses, opt_points, option);
    std::cout << "g_cw from BA estimation = \n" << pose->g_cw().matrix3x4() << std::endl;
    printf("offset = %f\n", offsetf);
    return;
}

