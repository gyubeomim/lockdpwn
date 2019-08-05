#ifndef DIRECT_H_
#define DIRECT_H_
#include "stdafx.h"
#include "../include/intrinsic.h"
#include "../include/optimizer.h"
#include "../include/optimizer_types.h"

// Huber loss C = e^2        : for |e| < a
//        or    = 2a|e|- a^2 : otherwise.
// C = W * e^2
// W = C / e^2
// therefore  W = 1.             : for |e|<a
//            W =  2a|e|-a^2 / e^2
inline real huber(const real& error, const real& a){
    real abs_e = std::abs(error);
    return (abs_e<a) ? 1. : a/abs_e;
}

cv::Mat cvt_8UC1(cv::Mat src);
cv::Mat pyrup_no_filter(const cv::Mat& im);
cv::Mat sub(cv::Mat im1_32f, cv::Mat im0_32f, cv::Scalar color);

struct ImInfo{
    float *im_ptr_, *ix_ptr_, *iy_ptr_;
    size_t im_es_, ix_es_;
    int hx_, hy_, rows_, cols_;

    ImInfo(cv::Mat mat_im);
    bool get_pixel(int index, real& i) const;
    ImInfo(cv::Mat mat_im, cv::Mat mat_ix, cv::Mat mat_iy);
    bool get_pixel(int index, real& i, real& ix, real&iy) const;
    Eigen::Matrix<int,2,1> get_dxy(int index) const;
};

class Images{
    public:
        int index_size(int level) const { const cv::Mat& im = im_.at(level); return im.rows * im.cols; }
        int patch_size(int level) const { return im_.at(level).cols; }
        const cv::Mat& src() const { return src_; };
        const std::vector<cv::Mat>& im() const { return im_; }
        const std::vector<cv::Mat>& ix() const { return ix_; }
        const std::vector<cv::Mat>& iy() const { return iy_; }

        static Images* for_frame(cv::Mat src, int levels){ return new Images(src,levels); }
        static Images* for_point(const std::vector<cv::Mat>& vim,
                const Eigen::Matrix<real,2,1>& uv, size_t patch_size){ return new Images(vim, uv, patch_size); }
        Images(cv::Mat src, int levels);
        Images(const std::vector<cv::Mat>& vim, const Eigen::Matrix<real,2,1>& uv, size_t patch_size);
    private:

        const cv::Mat src_;
        std::vector<cv::Mat> im_;
        std::vector<cv::Mat> ix_, iy_; // None for frame. exist onlky for point

};

inline real zoomout_ratio(const Eigen::Matrix<real,3,1>& Xc, real rho){
    real ratio = 1. / ( Xc[2] * rho);  // cam에서 가까울수록, Xc[2]가 작을수록 확대.
    ratio = std::max((real)1., ratio);
    ratio = std::min((real)4., ratio); // 2.
    return ratio;
}

cv::Mat warp(const std::vector<cv::Mat>&vim,
        const Eigen::Matrix<real,2,1>& x, // on level 0
        real zoom_out_ratio, int lv0,
        size_t patch_size);

// <<< to iamge process.h ??

// >>>>>>>>>>>>>>>>>>>>>>

class Point;
class DirProjEdge;
// Frame : 최적화argument-node와 관련된 edge/proj, 고유 id/intrinsic을 정의하는 class
class Frame{
public:
    Frame(cv::Mat src,
            int levels,
            const Intrinsic* ptr_intrinsic,
            int id);

    virtual ~Frame(){ delete images_; }
    Images* images() const { return images_; }
    std::set<Point*>& points() { return points_; }
    const std::set<Point*>& points() const { return points_; }
    const Intrinsic* intrinsic()const { return intrinsic_; }
    int id() const { return id_; }

    virtual const Sophus::SE3<real>& g_cw() const = 0;
    virtual const std::map<Point*, OptEdge<real>*>& proj_edges() const = 0;
    virtual std::map<Point*, OptEdge<real>*>& proj_edges() = 0;
    virtual OptNode<real>* node() const = 0;
private:
    Images*const images_;
    std::set<Point*> points_;
    const Intrinsic*const intrinsic_;
    const int id_;
};

class PoseFrame : public Frame {
public:
    PoseFrame(cv::Mat src,
            int levels,
            const Sophus::SE3<real>& g_cw,
            const Intrinsic* ptr_intrinsic,
            int id)
        : Frame(src, levels, ptr_intrinsic, id),
        node_(new PoseSE3<real>(g_cw, ExpMult::POST)) {
    }

    virtual ~PoseFrame(){
        // 노드를 삭제하는 순간.  나드 파괴자가 edge를 expire하고 삭제
        delete node_;
    }

    const Sophus::SE3<real>& g_cw() const { return node_->g_cw(); }
    const std::map<Point*, OptEdge<real>*>& proj_edges() const { return proj_edges_; }
    std::map<Point*, OptEdge<real>*>& proj_edges() { return proj_edges_; }
    OptNode<real>* node() const { return node_; }

private:
    PoseSE3<real>*const node_;
    std::map<Point*, OptEdge<real>*> proj_edges_;
};

class Point{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    Point(Frame* f0,
            const Eigen::Matrix<real,2,1>& uv0,
            const Eigen::Matrix<real,2,1>& n_uv0,
            int patch_size, int id);
    ~Point();
    Point3<real>* node() { return node_; }
    Images* patch() const { return patch_; }
    const Frame* frame0() const { return f0_; }
    Eigen::Matrix<real,2,1> uv0() const { return uv0_; }
    const Eigen::Matrix<real,2,1>& n_uv0() const { return node_->n_uv0(); }
    int id() const { return id_; }
private:
    Images*const patch_;
    const Eigen::Matrix<real,2,1> uv0_;
    Point3<real>* node_; // Has PoseSE3<real>* for f0
    const Frame*const f0_;
    const int id_;
};

class StereoEdge : public OptEdge<real> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    // variable nodes는 Point3 하나
    // 참조는 Point의patch0_, PoseSE3 p0, k번째 frame의 patch_, node_
    StereoEdge(Point* point,
            const Images* images1,
            const Sophus::SE3<real>& g_c0,
            const Intrinsic* intrinsic);
    void set_level(int lv) { lv_ = lv; }
    virtual typename OptEdge<real>::Type type() const{ return OptEdge<real>::Type::P; }
    virtual void update();
    virtual Eigen::Matrix<real,-1,1> error() const { return error_; }
    virtual const VectorVectorX<real>& jres() const { return jres_; }
    virtual const VectorMatrixX<real>& hessians() const { return hessians_; }
    virtual const std::vector<std::pair<OptNode<real>*, OptNode<real>*> >& hessians_domain() const { return hessians_domain_; }

private:
    Point*const point_;
    const Images*const images1_; // the z
    Eigen::Matrix<real,1,1> error_;
    std::vector<std::pair<OptNode<real>*, OptNode<real>*> > hessians_domain_;
    VectorMatrixX<real> hessians_; //, jacobians_;
    VectorVectorX<real> jres_;
    const Sophus::SE3<real> g_c0_;
    //const Eigen::Matrix<real,3,3>*const K_; // cam c의intrinsic
    const Intrinsic*const intrinsic_;
    int lv_;

};

class DirProjEdge : public OptEdge<real>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    DirProjEdge(PoseFrame* frame, Point* point);
    void set_level(int lv) { lv_ = lv; }
    virtual typename OptEdge<real>::Type type() const{ return OptEdge<real>::Type::F2P; }
    virtual void update();
    virtual Eigen::Matrix<real,-1,1> error() const { return error_; }
    virtual const VectorVectorX<real>& jres() const { return jres_; }
    virtual const VectorMatrixX<real>& hessians() const { return hessians_; }
    virtual const std::vector<std::pair<OptNode<real>*, OptNode<real>*> >& hessians_domain() const { return hessians_domain_; }

private:
    PoseFrame*const frame_;
    Point*const point_;
    Eigen::Matrix<real,1,1> error_;
    std::vector<std::pair<OptNode<real>*, OptNode<real>*> > hessians_domain_;
    VectorMatrixX<real> hessians_; //, jacobians_;
    VectorVectorX<real> jres_;
    int lv_;
};

class Visualizer : public OptInterface<real> {
public:
    Visualizer(const FeatureCriteria* feature_criteria = NULL)
        : frame_(NULL), lv_(0), stopmode_(false), feature_criteria_(feature_criteria)
    {
    }
    void set_level(int lv){ lv_ = lv; }
    void set_frame(Frame* frame){ frame_ = frame; }
    virtual void on_update(const OptInfo<real>& info);
    void set_stop(bool mode) { stopmode_ = mode; }
private:
    const FeatureCriteria*const feature_criteria_;
    Frame* frame_;
    int lv_;
    bool stopmode_;
};

class DirectMethod {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    DirectMethod(const Intrinsic* intrinsic);
    void set_stereo(const Sophus::SE3<real>* g_rl){ g_rl_ = g_rl; }
    void put_image(cv::Mat im0, cv::Mat im1);
private:
    Sophus::SE3<real> get_g_cw() const; // latest g_cw
    std::set<Point*> supply_points(Frame* frame);
    void stereo_invd(const std::set<Point*>& new_points, cv::Mat im_right, int end_level);
    void marginalize();
    bool is_keyframe(Frame* frame) const;

    std::map<int, Frame*> frames_;
    std::set<Frame*> fixed_frames_;
    std::map<int, Images*> im_right_;
    GeneralOptMarginals<real> marginals_;

    std::set<Point*> visible_points_;
    std::set<Point*> variable_points_;
    Sophus::SE3<real> g_cw_latest_;
    OptimizeBAOption<real> motion_option_;
    OptimizeBAOption<real> stereo_option_;
    OptimizeBAOption<real> bundle_option_;
    Visualizer visualizer_;
    //const Intrinsic intrinsic_;
    const Intrinsic*const intrinsic_;
    const Sophus::SE3<real>* g_rl_;
    int n_frame_;
    int n_point_;
    const int levels_;
    const int patch_size_;
};


class GammaFrame;
class GammaStereoFrame;
class StereoVisualizer : public OptInterface<real> {
public:
    StereoVisualizer()
        : frame_(NULL), frame_r_(NULL), lv_(0), stopmode_(false) {}
    void set_level(int lv){ lv_ = lv; }
    void set_frame(const GammaFrame* frame, const GammaStereoFrame* frame_r);
    void set_stop(bool mode) { stopmode_ = mode; }
    virtual void on_update(const OptInfo<real>& info);
private:
    const GammaFrame* frame_;
    const GammaStereoFrame* frame_r_;
    int lv_;
    bool stopmode_;
};

class GammaFrame;
class FisheyeDirectMethod{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    FisheyeDirectMethod(
            const Intrinsic* intrinsic0,
            const Intrinsic* intrinsic1,
            const Sophus::SE3<real>& g_rl,
            const FeatureCriteria* feature_criteria,
            int end_level);
    void put_image(cv::Mat im0, cv::Mat im1);

private:
    Sophus::SE3<real> get_g_cw() const{ return g_cw_latest_; }
    std::set<Point*> supply_points(GammaFrame* frame);
    void stereo_invd(const GammaFrame* frame, const std::set<Point*>& new_points, cv::Mat im_right, int end_level);

    std::map<int, Frame*> frames_;
    std::map<int, GammaStereoFrame*> frames_r_;


    Sophus::SE3<real> g_cw_latest_;
    std::set<Point*> visible_points_;
    std::set<Point*> variable_points_;

    Visualizer visualizer_;
    StereoVisualizer stereo_visualizer_;
    OptimizeBAOption<real> motion_option_;
    OptimizeBAOption<real> stereo_option_;
    OptimizeBAOption<real> bundle_option_;
    const Intrinsic*const intrinsic0_;
    const Intrinsic*const intrinsic1_;
    const Sophus::SE3<real> g_rl_;
    const FeatureCriteria*const feature_criteria_;
    int n_frame_;
    int n_point_;
    const int levels_;
    const int end_levels_;
    const int patch_size_;
};

void estimate_motion(OptNode<real>* pose,
        const std::set<DirProjEdge*>& prj_edges,
        int levels,
        int end_level,
        const OptimizeBAOption<real>& option);

void estimate_bundle(const std::map<int, Frame*>& frames, const OptimizeBAOption<real>& option);

void zoomout_test(cv::Mat im0);
void motion_invd_test(cv::Mat im0, cv::Mat im1, const Intrinsic* intrinsic, float offsetf, TestCase test_case);

cv::Mat draw_epipolar_line(GammaFrame* frame);
void graph_test();

#endif
