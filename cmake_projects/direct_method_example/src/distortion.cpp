#include "../include/direct.h"

// Photometric frame
// Considering exposure gamma gain
class GammaFrame : public Frame {
public:
    GammaFrame(cv::Mat src,
            int levels,
            const Sophus::SE3<real>& g_cw,
            const Intrinsic* ptr_intrinsic,
            int id)
        : Frame(src, levels, ptr_intrinsic, id),
        node_(new GammaPoseSE3<real>(g_cw, ExpMult::POST) )
    {

    }

    const Sophus::SE3<real>& g_cw() const { return node_->g_cw(); }
    const std::map<Point*, OptEdge<real>*>& proj_edges() const { return proj_edges_; }
    std::map<Point*, OptEdge<real>*>& proj_edges() { return proj_edges_; }
    OptNode<real>* node() const { return node_; }

private:
    GammaPoseSE3<real>*const node_;
    std::map<Point*, OptEdge<real>*> proj_edges_;
};

FisheyeDirectMethod::FisheyeDirectMethod(
        const Intrinsic* intrinsic0,
        const Intrinsic* intrinsic1,
        const Sophus::SE3<real>& g_rl,
        const FeatureCriteria* feature_criteria,
        int end_level)
    : intrinsic0_(intrinsic0),
    intrinsic1_(intrinsic1),
    g_rl_(g_rl),
    feature_criteria_(feature_criteria),
    n_frame_(0),
    n_point_(0),
    levels_(5),
    end_levels_(end_level),
    patch_size_(8),
    visualizer_(Visualizer(feature_criteria))
{
    motion_option_.n_iter = 10; // 50
    motion_option_.intf = &visualizer_;
    stereo_option_.n_iter = 10; // 10
    stereo_option_.intf = &stereo_visualizer_;
    stereo_visualizer_.set_stop(false);
    visualizer_.set_stop(false);
    bundle_option_.n_iter = 10; // 50
    motion_option_.motion_update_ratio = 0.5;
    bundle_option_.motion_update_ratio = 0.2;
    bundle_option_.intf = &visualizer_;

    //g_cw_latest_.translation() = Eigen::Matrix<real,3,1>(-10., -20., -30.);
}

std::set<Point*> FisheyeDirectMethod::supply_points(GammaFrame* frame){
    Images* images = frame->images();
    cv::Mat src = images->src();
    std::set<Point*> new_points;
    const std::vector<cv::Point2f> corners = feature_criteria_->corrner_detect(src);
    const size_t max_points = feature_criteria_->max_points_for_frame();
    for(size_t i=0; i < corners.size(); i++){
        if(frame->points().size() >= max_points) break;
        auto & corner = corners[i];
        Eigen::Matrix<real, 2,1> uv(corner.x, corner.y);
        bool duplicate = false;
        if(!feature_criteria_->is_enable_point(uv))
            continue;
        const auto n_uv =frame->intrinsic()->unproj(uv);
        Point* point = new Point(frame, uv, n_uv, patch_size_, n_point_++);
        point->node()->set_depth(1.);
        frame->points().insert(point); // f1 stereo.
        new_points.insert(point);
    }
    std::cout << " per init points " << corners.size() << std::endl;
    return new_points;
}

class GammaStereoFrame { // Rightside state
public:
    GammaStereoFrame(cv::Mat src,
            int levels,
            const Sophus::SE3<real>* g_rl,
            const Intrinsic* ptr_intrinsic)
        : images_(Images::for_frame(src, levels)),
        node_(new GammaState<real>()),
        intrinsic_(ptr_intrinsic),
        g_rl_(g_rl)
    {

    }

    GammaState<real>* node() const { return node_; }
    const Sophus::SE3<real>& g_rl() const { return *g_rl_; }
    const Intrinsic* intrinsic() const { return intrinsic_; }
    const Images* images() const { return images_; }

private:
    Images*const images_;
    GammaState<real>*const node_;
    const Intrinsic*const intrinsic_;
    const Sophus::SE3<real>*const g_rl_;
};

class PhStereoEdge : public OptEdge<real>{
    // Photometric projection edge
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    PhStereoEdge(GammaStereoFrame* frame_r, Point* point)
    : frame_r_(frame_r),
    point_(point),
    lv_(-1) {
        GammaState<real>*f = dynamic_cast<GammaState<real>*>(frame_r_->node());
        OptNode<real>* pt = point_->node();
        OptEdge<real>::nodes().push_back(f);
        OptEdge<real>::nodes().push_back(pt);
        f->addEdge(this); // gamma
        pt->addEdge(this);
        Eigen::Matrix<real,1,2> ja;
        Eigen::Matrix<real,1,1> jb;
        hessians_.push_back(ja.transpose()*ja);
        hessians_.push_back(jb.transpose()*jb);
        hessians_.push_back(ja.transpose()*jb);
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, f));
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(pt, pt));
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, pt));
        jres_.push_back(Eigen::Matrix<real,2,1>());
        jres_.push_back(Eigen::Matrix<real,1,1>());
    }
    void set_level(int lv) { lv_ = lv; }
    virtual typename OptEdge<real>::Type type() const{ return OptEdge<real>::Type::F2P; }
    virtual void update(){
        GammaState<real>* gamma = frame_r_->node();
        Point3<real>* pt = point_->node();
        const real rho = pt->invd();
        const auto xbar0 = point_->n_uv0();
        const auto& g_c0 = frame_r_->g_rl();
        const auto X0 = pt->x0();
        const auto Xc = g_c0 * X0;
        const Intrinsic* intrinsic_c = frame_r_->intrinsic();
        const Intrinsic* intrinsic0 = point_->frame0()->intrinsic();
        const auto& K0 = intrinsic0->K();
        const auto& Kc = intrinsic_c->K();
        real scale = std::pow(0.5, (real)lv_);
        Eigen::Matrix<real,2,1> xbar_c = Xc.head<2>() / Xc[2];
        // common
        Eigen::Matrix<real,2,2> d_xtilde0_d_xbar0 = intrinsic0->jac_dxtilde_dxbar(xbar0);
        Eigen::Matrix<real,2,2> d_x0_d_xbar0 = scale*K0.block<2,2>(0,0)*d_xtilde0_d_xbar0;
        // jb
        Eigen::Matrix<real,2,3> d_xbar_c_d_Xc;{
            real v = 1./Xc[2];
            real v2 = v*v;
            d_xbar_c_d_Xc << v, 0., -Xc[0]*v2,
                         0., v, -Xc[1]*v2;
        }
        Eigen::Matrix<real,3,1> d_X0_drho;
        Eigen::Matrix<real,3,2> d_X0_d_xbar0;{
            real v = X0[2];
            real v2 = v*v;
            d_X0_d_xbar0 << v, 0.,
                            0., v,
                            0., 0.;
            d_X0_drho << -xbar0[0]*v2, -xbar0[1]*v2, -v2;
        }
        Eigen::Matrix<real,3,2> d_X0_dx0 = d_X0_d_xbar0 * d_x0_d_xbar0.inverse();
        Eigen::Matrix<real,2,2> d_xtilde_c_d_xbar_c = intrinsic_c->jac_dxtilde_dxbar(xbar_c);
        Eigen::Matrix<real,2,3> d_xc_d_Xc = scale*Kc.block<2,2>(0,0) * d_xtilde_c_d_xbar_c * d_xbar_c_d_Xc;
        Eigen::Matrix<real,2,2> d_xc_d_x0 = d_xc_d_Xc * g_c0.rotationMatrix() * d_X0_dx0;

        const int index_size = point_->patch()->index_size(lv_); // 1열로 풀어넣은것
        const int patch_size = point_->patch()->patch_size(lv_); // index_size의 sqrt
        const Images* patch = point_->patch();
        real ratio = zoomout_ratio(Xc, rho);
        const Eigen::Matrix<real,2,1> xr = intrinsic_c->proj(Xc);
        cv::Mat im1 = warp(frame_r_->images()->im(), xr, ratio, lv_, patch_size);
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
            const Eigen::Matrix<real,1,2> ja(0., 0.); // TODO 제대로 된 gamma 자코비안 모델 적용
            const Eigen::Matrix<real,1,1> jb
                = - gI0 * d_xc_d_x0.inverse() * d_xc_d_Xc * g_c0.rotationMatrix() * d_X0_drho;

            real W = huber(err(0), 30.);
            hessians_[0] += W * ja.transpose()*ja;
            hessians_[1] += W * jb.transpose()*jb;
            hessians_[2] += W * ja.transpose()*jb;
            jres_[0]     += W * ja.transpose()*err;
            jres_[1]     += W * jb.transpose()*err;
        }
        // TODO Pseudo gamma
        hessians_[0].setIdentity();
        return;
    }
    virtual Eigen::Matrix<real,-1,1> error() const { return error_; }
    virtual const VectorVectorX<real>& jres() const { return jres_; }
    virtual const VectorMatrixX<real>& hessians() const { return hessians_; }
    virtual const std::vector<std::pair<OptNode<real>*, OptNode<real>*> >& hessians_domain() const { return hessians_domain_; }
private:
    GammaStereoFrame*const frame_r_; // Gamma 추정때문에 필요.
    Point*const point_;
    Eigen::Matrix<real,1,1> error_;
    std::vector<std::pair<OptNode<real>*, OptNode<real>*> > hessians_domain_;
    VectorMatrixX<real> hessians_;
    VectorVectorX<real> jres_;
    int lv_;
};

class GammaPoseSE3PriorEdge : public OptEdge<real>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    GammaPoseSE3PriorEdge(GammaFrame* frame)
    : frame_(frame){
        OptNode<real>* f = frame->node();
        OptEdge<real>::nodes().push_back(f);
        f->addEdge(this);
        Eigen::Matrix<real,2,8> ja; // 6dof SE(3) + 2 photometric gamma
        hessians_.push_back(ja.transpose()*ja);
        jres_.push_back(Eigen::Matrix<real,2,1>());
    }

    virtual typename OptEdge<real>::Type type() const{ return OptEdge<real>::Type::F2F; }
    virtual Eigen::Matrix<real,-1,1> error() const { return error_; }
    virtual const VectorVectorX<real>& jres() const { return jres_; }
    virtual const VectorMatrixX<real>& hessians() const { return hessians_; }
    virtual const std::vector<std::pair<OptNode<real>*, OptNode<real>*> >& hessians_domain() const { return hessians_domain_; }

    virtual void update(){
        GammaPoseSE3<real>* pose = dynamic_cast<GammaPoseSE3<real>*>(frame_->node());
        Eigen::Matrix<real,2,8> ja;
        ja.setZero();
        ja.block<2,2>(0,6) << 1., 0.,
                              0., 1.;
        //ja *= 1e+7;
        error_ = pose->gamma() - Eigen::Matrix<real,2,1>(1., 1.);
        hessians_[0] = ja.transpose() * ja;
        jres_[0] = ja.transpose() * error_;
    }

private:
    Eigen::Matrix<real,2,1> error_;
    std::vector<std::pair<OptNode<real>*, OptNode<real>*> > hessians_domain_;
    VectorMatrixX<real> hessians_; //, jacobians_;
    VectorVectorX<real> jres_;

    GammaFrame*const frame_;

};

class PhProjEdge : public OptEdge<real>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    PhProjEdge(GammaFrame* frame, Point* point, const FeatureCriteria* feature_criteria)
    : frame_(frame), point_(point), lv_(-1), feature_criteria_(feature_criteria) {
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
        Eigen::Matrix<real,1,8> ja; // 6dof SE(3) + 2 photometric gamma
        Eigen::Matrix<real,1,1> jb; // inverse depth
        hessians_.push_back(ja.transpose()*ja);
        hessians_.push_back(jb.transpose()*jb);
        hessians_.push_back(ja.transpose()*jb);
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, f));
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(pt, pt));
        hessians_domain_.push_back(std::pair<OptNode<real>*,OptNode<real>*>(f, pt));
        jres_.push_back(Eigen::Matrix<real,8,1>());
        jres_.push_back(Eigen::Matrix<real,1,1>());
    }

    virtual void update(){
        for(size_t i = 0; i < hessians_.size(); i++) hessians_[i].setZero();
        for(size_t i = 0; i < jres_.size(); i++)     jres_[i].setZero();
        error_.setZero();

        GammaPoseSE3<real>* pose = dynamic_cast<GammaPoseSE3<real>*>(frame_->node());
        Point3<real>* pt = point_->node();
        const Frame* frame0 = point_->frame0();
        const real rho = pt->invd();
        const auto xbar0 = point_->n_uv0();
        const auto& g_cw = frame_->g_cw();
        const auto g_0w = frame0->g_cw();
        const auto g_c0 = g_cw * g_0w.inverse();
        const auto X0 = pt->x0();
        const auto Xw = pt->xw();
        const auto Xc = g_cw * Xw;
        const Intrinsic* intrinsic0 = frame0->intrinsic();
        const Intrinsic* intrinsic_c = frame_->intrinsic();
        const auto& K0 = intrinsic0->K();
        const auto& Kc = intrinsic_c->K();
        const Eigen::Matrix<real,2,1> xc = intrinsic_c->proj(Xc);
        if(!feature_criteria_->is_enable_point(xc))
            return;

        real scale = std::pow(0.5, (real)lv_);
        Eigen::Matrix<real,2,1> xbar_c = Xc.head<2>() / Xc[2];
        // common element for ja / jb
        Eigen::Matrix<real,2,2> d_xtilde0_d_xbar0 = intrinsic0->jac_dxtilde_dxbar(xbar0);
        Eigen::Matrix<real,2,2> d_x0_d_xbar0 = scale*K0.block<2,2>(0,0)*d_xtilde0_d_xbar0;
        // element for ja
        Eigen::Matrix<real,2,3> d_xbar0_d_X0;{
            real v = rho; // 1./X0[2]
            real v2 = v*v;
            d_xbar0_d_X0 << v, 0., -X0[0]*v2,
                            0., v, -X0[1]*v2;
        }
        Eigen::Matrix<real,2,3> d_x0_dX0 = d_x0_d_xbar0 * d_xbar0_d_X0;
        Eigen::Matrix<real,3,6> d_Xw_d_xi;{
            d_Xw_d_xi.block<3,3>(0,0).setIdentity();
            d_Xw_d_xi.block<3,3>(0,3) = -skew(Xw);
        }
        // element for jb
        Eigen::Matrix<real,2,3> d_xbar_c_d_Xc;{
            real v = 1./Xc[2];
            real v2 = v*v;
            d_xbar_c_d_Xc << v, 0., -Xc[0]*v2,
                         0., v, -Xc[1]*v2;
        }
        Eigen::Matrix<real,2,2> d_xtilde_c_d_xbar_c = intrinsic_c->jac_dxtilde_dxbar(xbar_c);
        Eigen::Matrix<real,2,3> d_xc_d_Xc = scale*Kc.block<2,2>(0,0) * d_xtilde_c_d_xbar_c * d_xbar_c_d_Xc;
        Eigen::Matrix<real,3,1> d_X0_drho;
        Eigen::Matrix<real,3,2> d_X0_d_xbar0;{
            real v = X0[2];
            real v2 = v*v;
            d_X0_d_xbar0 << v, 0.,
                            0., v,
                            0., 0.;
            d_X0_drho << -xbar0[0]*v2, -xbar0[1]*v2, -v2;
        }
        Eigen::Matrix<real,3,2> d_X0_dx0 = d_X0_d_xbar0 * d_x0_d_xbar0.inverse();
        Eigen::Matrix<real,2,2> d_xc_d_x0 = d_xc_d_Xc * g_c0.rotationMatrix() * d_X0_dx0;

        // TODO derivation 수식 markdown에 정리.
        const int index_size = point_->patch()->index_size(lv_); // 1열로 풀어넣은것
        const int patch_size = point_->patch()->patch_size(lv_); // index_size의 sqrt
        const Images* patch = point_->patch();
        real ratio = zoomout_ratio(Xc, rho);
        cv::Mat im1 = warp(frame_->images()->im(), xc, ratio, lv_, patch_size);
        const ImInfo info0( patch->im().at(lv_), patch->ix().at(lv_), patch->iy().at(lv_) );
        const ImInfo info1( im1 );
        for(int index = 0; index < index_size; index++){
            real i0, ix, iy, i1;
            bool c0 = info0.get_pixel(index, i0, ix, iy);
            bool c1 = info1.get_pixel(index, i1);
            if(!c0) continue;
            if(!c1) continue;
            Eigen::Matrix<real,1,1> err(i0-i1);
            Eigen::Matrix<real,1,2> gI0(ix,iy);
            Eigen::Matrix<real,1,8> ja;
            ja.setZero();
            ja.block<1,6>(0,0) = gI0 * d_x0_dX0 * g_0w.rotationMatrix() * d_Xw_d_xi;
            const Eigen::Matrix<real,1,1> jb
                = - gI0 * d_xc_d_x0.inverse() * d_xc_d_Xc * g_c0.rotationMatrix() * d_X0_drho;

            real W = huber(err(0), 30.);
            hessians_[0] += W * ja.transpose()*ja;
            hessians_[1] += W * jb.transpose()*jb;
            hessians_[2] += W * ja.transpose()*jb;
            jres_[0]     += W * ja.transpose()*err;
            jres_[1]     += W * jb.transpose()*err;
            error_       += err;
        }
    }
    void set_level(int lv) { lv_ = lv; }
    virtual typename OptEdge<real>::Type type() const{ return OptEdge<real>::Type::F2P; }
    virtual Eigen::Matrix<real,-1,1> error() const { return error_; }
    virtual const VectorVectorX<real>& jres() const { return jres_; }
    virtual const VectorMatrixX<real>& hessians() const { return hessians_; }
    virtual const std::vector<std::pair<OptNode<real>*, OptNode<real>*> >& hessians_domain() const { return hessians_domain_; }

private:
    const FeatureCriteria*const feature_criteria_;
    GammaFrame*const frame_;
    Point*const point_;
    Eigen::Matrix<real,1,1> error_;
    std::vector<std::pair<OptNode<real>*, OptNode<real>*> > hessians_domain_;
    VectorMatrixX<real> hessians_; //, jacobians_;
    VectorVectorX<real> jres_;
    int lv_;
    //GammaPoseSE3<real>
};

void StereoVisualizer::set_frame(const GammaFrame* frame, const GammaStereoFrame* frame_r){
    frame_ = frame;
    frame_r_ = frame_r;
}

void StereoVisualizer::on_update(const OptInfo<real>& info){
    cv::Mat dst0 = frame_->images()->src().clone();
    cv::Mat dst1 = frame_r_->images()->src().clone();
    cv::cvtColor(dst0, dst0, cv::COLOR_GRAY2RGB);
    cv::cvtColor(dst1, dst1, cv::COLOR_GRAY2RGB);
    real alg_scale = std::pow(0.5, (real)lv_);
    real dst_scale = 1.;
    std::map<int, Point*> points;
    size_t patch_size = -1;
    for(auto it_point = frame_->points().begin(); it_point != frame_->points().end(); it_point++){
        Point* point = (*it_point);
        points[point->id()] = point;
        if(it_point == frame_->points().begin()){
            Images* patch = point->patch();
            patch_size = patch->patch_size(lv_);
        }
    }
    for(auto it = points.begin(); it != points.end(); it++){
        Point* point = it->second;
        Point3<real>* pt = point->node();
        std::stringstream str_id;
        str_id << boost::format("%ld") % point->id();
        Images* patch = point->patch();
        Eigen::Matrix<real,3,1> X0 = pt->x0();
        Eigen::Matrix<real,3,1> Xc =  frame_r_->g_rl() * X0;
        Eigen::Matrix<real,2,1> uv1 = frame_r_->intrinsic()->proj(Xc);
        cv::Point2f cv_uv0(point->uv0().x()*dst_scale, point->uv0().y()*dst_scale);
        cv::Point2f cv_uv( uv1.x()*dst_scale, uv1.y()*dst_scale);
        cv::Point2f hb(patch_size/2./alg_scale*dst_scale, patch_size/2./alg_scale*dst_scale);
        real ratio = zoomout_ratio(Xc, pt->invd());
        cv::rectangle(dst1, cv_uv-ratio*hb, cv_uv+ratio*hb, CV_RGB(0,0,255), 1);
        cv::rectangle(dst0, cv_uv0-hb, cv_uv0+hb, CV_RGB(0,255,0), 1);
        cv::rectangle(dst1,  cv_uv-hb,  cv_uv+hb, CV_RGB(0,255,0), 1);
        cv::circle(dst0, cv_uv0, 3, CV_RGB(0, 255, 0), 1);
        cv::circle(dst1,  cv_uv, 3, CV_RGB(0, 255, 0), 1);
        std::stringstream str_rho;
        str_rho << boost::format("%.4f") % (1./pt->invd());
        cv::putText(dst0, str_id.str(), cv_uv0+cv::Point2f(10.,10.),
                cv::FONT_HERSHEY_PLAIN, 1., CV_RGB(0, 0, 255), 1);
        cv::putText(dst1, str_id.str(), cv_uv+cv::Point2f(10.,10.),
                cv::FONT_HERSHEY_PLAIN, 1., CV_RGB(0, 0, 255), 1);
        cv::putText(dst1, str_rho.str(), cv_uv+cv::Point2f(10.,20.),
                cv::FONT_HERSHEY_PLAIN, 0.8, CV_RGB(255, 0, 0), 1);
    }
    cv::imshow("dst0", dst0);
    cv::imshow("dst1", dst1);
    static int i = 0;
    if(i++==0){
        cv::moveWindow("dst0", 500, 100);
        cv::moveWindow("dst1", 900, 100);
    }
    if(info.error_)
        set_stop(true);
    char c = cv::waitKey(stopmode_?0:1);
    if(c == 'q') exit(1);
    else if(c == 's') stopmode_ = !stopmode_;
    return;
}

cv::Mat draw_epipolar_line(GammaStereoFrame* frame_r, const std::set<Point*>& points ){
    cv::Mat dst = frame_r->images()->src().clone();
    cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);
    std::vector<real> depths;
    for(real z = 0.1; z < 1000.; z*=1.5)
        depths.push_back(z);

    for(auto it_point = points.begin(); it_point != points.end(); it_point++){
        auto node = (*it_point)->node();
        real z_org = 1./node->invd();
        for(int i = 0; i < depths.size()-1; i++){
            double z0 = depths.at(i);
            double z1 = depths.at(i+1);
            cv::Point2d pt0, pt1;
            {
                node->set_depth(z0);
                Eigen::Matrix<real,3,1> Xc = frame_r->g_rl()*node->x0();
                Eigen::Matrix<real,2,1> uv = frame_r->intrinsic()->proj(Xc);
                pt0 = cv::Point2d(uv[0], uv[1]);
            } {
                node->set_depth(z1);
                Eigen::Matrix<real,3,1> Xc = frame_r->g_rl()*node->x0();
                Eigen::Matrix<real,2,1> uv = frame_r->intrinsic()->proj(Xc);
                pt1 = cv::Point2d(uv[0], uv[1]);
            }
            cv::line(dst, pt0, pt1, CV_RGB(255,0,0), 1);
            if(i+2==depths.size())
                cv::circle(dst, pt1, 3,  CV_RGB(255,0,0), -1);
        }
        node->set_depth(z_org);
    }
    return dst;
}

void FisheyeDirectMethod::stereo_invd(const GammaFrame* frame, const std::set<Point*>& new_points, cv::Mat im_right, int end_level){
    GammaStereoFrame* frame_r = new GammaStereoFrame(im_right, levels_, &g_rl_, intrinsic1_);
    stereo_visualizer_.set_frame(frame, frame_r);
    frames_r_[frame->id()] = frame_r;
    // TODO 실제 point의 depth를 바꾸지 않고, 또는 원상복구 시키는걸로 그려야함.
    //cv::Mat epip = draw_epipolar_line(frame_r, frame->points());
    //cv::imshow("epip", epip);
    //cv::moveWindow("epip", 100, 100);
    std::set<PhStereoEdge*> edges;
    std::set<OptNode<real>*> opt_points;
    std::set<OptNode<real>*> opt_gamma = {frame_r->node(), };
    frame_r->node()->fix(true);
    for(auto it_point = new_points.begin(); it_point != new_points.end(); it_point++){
        Point* point = *it_point;
        PhStereoEdge* e = new PhStereoEdge(frame_r, point);
        edges.insert(e);
        opt_points.insert(point->node());
    }
    for(int lv = levels_-1; lv > end_level-1; lv--){
        if(StereoVisualizer* ptr = (StereoVisualizer*)stereo_option_.intf )
            ptr->set_level(lv);

        for(auto it_e = edges.begin(); it_e != edges.end(); it_e++)
            (*it_e)->set_level(lv);
        optimize_ba<real>(1, opt_gamma, opt_points, stereo_option_);
    }
}

std::set<PhProjEdge*> track(const std::set<Point*>& visible_points, GammaFrame* frame, const FeatureCriteria* feature_criteria){
    std::set<PhProjEdge*> prj_edges;
    for(auto it_point = visible_points.begin(); it_point != visible_points.end(); it_point++)
        frame->points().insert(*it_point);
    for(auto it = frame->points().begin(); it != frame->points().end(); it++){
        Point* point = *it;
        PhProjEdge* edge = new PhProjEdge(frame, point, feature_criteria);
        frame->proj_edges()[point] = edge;
        prj_edges.insert(edge);
    }
    return prj_edges;
};

void filter(Frame* frame, int end_level, const FeatureCriteria* feature_criteria){
    Images* images1 = frame->images();
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
        if(!feature_criteria->is_enable_point(uv1))
            outlier = true;
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

void estimate_motion(OptNode<real>* pose,
        const std::set<PhProjEdge*>& prj_edges,
        int levels,
        int end_level,
        const OptimizeBAOption<real>& option){
    if(option.marginals){
        printf("Error : Marginals must be NULL for estimate_motion\n");
        throw 1;
    }
    Visualizer* vis = NULL;
    if(option.intf){
        vis = dynamic_cast<Visualizer*>(option.intf);
        //vis->set_stop(true);
    }
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

// TODO FEJ 다시 적용: Abstract OptEdge에 update외에, pre_update 추가선언
// ===============================================================================================
void FisheyeDirectMethod::put_image(cv::Mat im0, cv::Mat im1){
    static int count = 0;
    OptNode<real>::set_print_create_destruct(false);
    OptEdge<real>::set_print_create_destruct(false);
    GammaFrame* frame0 = NULL;
    if(frames_.size()>0)
        frame0 = dynamic_cast<GammaFrame*>(frames_.rbegin()->second);
    GammaFrame* frame = new GammaFrame(im0, levels_, get_g_cw(), intrinsic0_, n_frame_);
    frames_[frame->id()] = frame;
    int end_level = 1;
    if(!frame0)
        frame->node()->fix(true);
    else{
        Visualizer* vis = dynamic_cast<Visualizer*>(motion_option_.intf);
        vis->set_frame(frame);
        auto prior = new GammaPoseSE3PriorEdge(frame);
        std::set<PhProjEdge*> prj_edges
            = track(visible_points_, dynamic_cast<GammaFrame*>(frame), feature_criteria_);
        estimate_motion(frame->node(), prj_edges, levels_, end_levels_, motion_option_);
        filter(frame, end_level, feature_criteria_);
        visible_points_ = frame->points();
        estimate_bundle(frames_, bundle_option_);
    }
    g_cw_latest_ = frame->g_cw();
    if(feature_criteria_->is_keyframe(frame)){
        printf("keyframe count %d keyframe %d\n", count, frame->id());
        //visualizer_.set_frame(frame);
        //if(frame->id() > 0)
        //    marginalize();
        std::set<Point*> new_points = supply_points(frame);
        visible_points_ = frame->points();
        variable_points_.insert(new_points.begin(),new_points.end());
        stereo_invd(frame, new_points, im1, end_level); // increase im_right_
        n_frame_++;
    }
    else{
        printf("none keyframe\n");
        frames_.erase(frame->id());
        OptNode<real>* node = frame->node();
        auto cp_edges = node->edges();
        for(auto it_edge = cp_edges.begin();
                it_edge != cp_edges.end();
                it_edge++){
            OptEdge<real>* edge = *it_edge;
            edge->expire();
            delete edge;
        }
        delete frame;
    }
    count++;
    return;
}
