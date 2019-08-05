#ifndef INTRINSIC_H_
#define INTRINSIC_H_
#include "../include/stdafx.h"

class Rectifier;

class Intrinsic{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    Intrinsic(const Eigen::Matrix<real,3,3>& K) : K_(K), invK_(K.inverse()) { }
    const Eigen::Matrix<real,3,3>& K() const { return K_; }
    const Eigen::Matrix<real,3,3>& invK() const { return invK_; }
    virtual Eigen::Matrix<real,2,1> undistort(const Eigen::Matrix<real,2,1>& xd) const;
    // from uv to xbar
    Eigen::Matrix<real,2,1> unproj(const Eigen::Matrix<real,2,1>& uv) const;
    // Xc to uv
    Eigen::Matrix<real,2,1> proj(const Eigen::Matrix<real, 3,1>& Xc) const;

    virtual Eigen::Matrix<real,2,2> jac_dxtilde_dxbar(const Eigen::Matrix<real,2,1>& xbar) const = 0;
    virtual Rectifier* create_rectifier() const = 0;

protected:
    // xbar to xtilde
    virtual Eigen::Matrix<real,2,1> distort(const Eigen::Matrix<real,2,1>& xbar) const = 0;

private:
    const Eigen::Matrix<real,3,3> K_;
    const Eigen::Matrix<real,3,3> invK_;
};

class Rectifier{
public:
    virtual cv::Mat rectify(cv::Mat src) const = 0;
    virtual void set_zoom_ratio(double zoom_ratio) = 0;

};

class RadTanRectifier : public Rectifier{
public:
    RadTanRectifier( const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion);
    virtual cv::Mat rectify(cv::Mat src) const;
    virtual void set_zoom_ratio(double zoom_ratio);
private:
    cv::Mat K0_;
    cv::Mat distortion_;
    cv::Mat map1_, map2_;
};

class FisheyeRectifier : public Rectifier{
public:
    FisheyeRectifier( const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion);
    virtual cv::Mat rectify(cv::Mat src) const;
    virtual void set_zoom_ratio(double zoom_ratio);
private:
    cv::Mat K0_;
    cv::Mat distortion_;
    cv::Mat map1_, map2_;
};

// 광각에선 fisheye보다 부정확해서 안쓸꺼지만, 일단 구현만
// https://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html?highlight=calib
class RadTanIntrinsic : public Intrinsic {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    RadTanIntrinsic(const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion)
        : Intrinsic(K), distortion_(distortion) { }
    virtual Eigen::Matrix<real,2,2> jac_dxtilde_dxbar(const Eigen::Matrix<real,2,1>& xbar) const;
    virtual Rectifier* create_rectifier() const { return new RadTanRectifier(K(), distortion_); }
protected :
    virtual Eigen::Matrix<real,2,1> distort(const Eigen::Matrix<real,2,1>& xbar) const;
private:
    Eigen::Matrix<real,4,1> distortion_;
};

// https://docs.opencv.org/2.4.13.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#fisheye
class FisheyeIntrinsic : public Intrinsic {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    FisheyeIntrinsic(const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion)
        : Intrinsic(K), distortion_(distortion) { }
    virtual Eigen::Matrix<real,2,1> undistort(const Eigen::Matrix<real,2,1>& xd) const;
    virtual Eigen::Matrix<real,2,2> jac_dxtilde_dxbar(const Eigen::Matrix<real,2,1>& xbar) const;
    virtual Rectifier* create_rectifier() const { return new FisheyeRectifier(K(), distortion_); }
protected:
    virtual Eigen::Matrix<real,2,1> distort(const Eigen::Matrix<real,2,1>& xbar) const;
private:
    Eigen::Matrix<real,4,1> distortion_;
};

class Frame;
class FeatureCriteria {
public:
    virtual size_t max_points_for_frame() const {
        throw 1;
    }
    virtual std::vector<cv::Point2f> corrner_detect(cv::Mat src) const{
        throw 1;
    }
    virtual bool is_enable_point(const Eigen::Matrix<real,2,1>& uv) const{
        throw 1;
    }
    virtual cv::Mat draw_mask(cv::Mat src) const {
        throw 1;
    }
    virtual bool is_keyframe(const Frame* points) const{
        throw 1;
    }

};


void distortion_test();

#endif
