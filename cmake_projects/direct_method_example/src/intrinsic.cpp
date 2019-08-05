#include "../include/intrinsic.h"

Eigen::Matrix<real,2,1> Intrinsic::undistort(const Eigen::Matrix<real,2,1>& xd) const{
    Eigen::Matrix<real,2,1> xbar = xd;
    for(size_t i = 0; i < 50; i++)
        xbar = xbar - distort(xbar) + xd;
    return xbar;
}

Eigen::Matrix<real,2,1> Intrinsic::unproj(const Eigen::Matrix<real,2,1>& uv) const{
    Eigen::Matrix<real,2,1> xtilde( (uv.x()-K()(0,2))/K()(0,0),
            (uv.y()-K()(1,2))/K()(1,1));
    Eigen::Matrix<real,2,1> xbar = undistort(xtilde);
    return xbar;
}

Eigen::Matrix<real,2,1> Intrinsic::proj(const Eigen::Matrix<real, 3,1>& Xc) const {
    Eigen::Matrix<real,2,1> xbar = Xc.head<2>() / Xc.z();
    Eigen::Matrix<real,2,1> xtilde = distort(xbar);
    Eigen::Matrix<real,2,1> uv = K().block<2,2>(0,0) * xtilde + K().block<2,1>(0,2);
    return uv;
}

RadTanRectifier::RadTanRectifier( const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion){
    distortion_ = (cv::Mat_<float>(4,1)<< distortion(0,0),
            distortion(1,0), distortion(2,0), distortion(3,0));
    K0_  = (cv::Mat_<float>(3,3) << K(0,0), 0., K(0,2),
            0., K(1,1), K(1,2),
            0., 0., 1.);
    set_zoom_ratio(0.2);
}

cv::Mat RadTanRectifier::rectify(cv::Mat src) const{
    cv::Mat dst;
    cv::remap(src, dst, map1_, map2_, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
    return dst;
}

void RadTanRectifier::set_zoom_ratio(double zoom_ratio){
    cv::Mat K = K0_.clone();
    K.at<float>(0,2) = 500.;
    K.at<float>(1,2) = 300.;
    K.at<float>(0,0) *= zoom_ratio;
    K.at<float>(1,1) *= zoom_ratio;
    cv::initUndistortRectifyMap(K0_, distortion_, cv::Mat::eye(3,3,CV_32F),
            K, cv::Size(1000,600), CV_32FC1, map1_, map2_);
}


Eigen::Matrix<real,2,1> RadTanIntrinsic::distort(const Eigen::Matrix<real,2,1>& xbar) const {
    real x2 = xbar[0]*xbar[0];
    real y2 = xbar[1]*xbar[1];
    real xy = xbar[0]*xbar[1];
    real r2 = x2 + y2;
    real r4 = r2*r2;
    const real& k1 = distortion_[0];
    const real& k2 = distortion_[1];
    const real& p1 = distortion_[2];
    const real& p2 = distortion_[3];
    real t1 = 1. + k1*r2 + k2*r4;
    real xd = xbar[0]*t1 + 2.*p1*xy + p2*(r2+2.*x2);
    real yd = xbar[1]*t1 + p1*(r2+2.*y2) + 2.*p2*xy;
    return Eigen::Matrix<real,2,1>(xd,yd);
}

Eigen::Matrix<real,2,2> RadTanIntrinsic::jac_dxtilde_dxbar(const Eigen::Matrix<real,2,1>& xbar) const{
    Eigen::Matrix<real,2,2> jac;
    real x2 = xbar[0]*xbar[0];
    real y2 = xbar[1]*xbar[1];
    real xy = xbar[0]*xbar[1];
    real r2 = x2 + y2;
    real r = std::sqrt(r2);
    real r3 = r*r2;
    real r4 = r2*r2;
    real r5 = r*r4;
    real r6 = r2*r4;
    const real& k1 = distortion_[0];
    const real& k2 = distortion_[1];
    const real& p1 = distortion_[2];
    const real& p2 = distortion_[3];
    real t1 = 1. + k1*r2 + k2*r4; // + k3*r6;
    real drdx = xbar[0]/r;
    real drdy = xbar[1]/r;
    real dt1dr = 2.*k1*r+4.*k2*r3;
    real dt1dx = dt1dr*drdx;
    real dt1dy = dt1dr*drdy;
    /*
       t1 = 1. + k1*r^2 + k2*r^4;
       dx''/dx' = t1 + x'*dt1/dx' + 2.*p1*y' + p2*(2.*r*dr/dx' + 4.*x')
       dy''/dx' = y'*dt1/dx' + 2.*p1*(2.*r*dr/dx') + 2.*p2*y'
       dx''/dy' = x'*dt1/dy' + 2.*p1*x' + p2*(2.*r*dr/dy')
       dy''/dy' = t1 + y'*dt1/dy' + 2.*p1*(2.*r*dr/dy'+4.*y') + 2.*p2*x'
       dt1/dx' = (2.*k1*r+4.*k2*r^3)*dr/dx'
       dt1/dy' = (2.*k1*r+4.*k2*r^3)*dr/dy'
       dr/dx' = x'/r
       dr/dy' = y'/r
       */
    jac(0,0) = t1 + xbar[0]*dt1dx + 2.*p1*xbar[1] + p2*(2.*r*drdx + 4.*xbar[0]);
    jac(0,1) = xbar[0]*dt1dy + 2.*p1*xbar[0] + p2*(2.*r*drdy);
    jac(1,0) = xbar[1]*dt1dx + p1*(2.*r*drdx) + 2.*p2*xbar[1];
    jac(1,1) = t1 + xbar[1]*dt1dy + p1*(2.*r*drdy + 4.*xbar[1]) + 2.*p2*xbar[0];
    return jac;
}

FisheyeRectifier::FisheyeRectifier(const Eigen::Matrix<real,3,3>& K, const Eigen::Matrix<real,4,1>& distortion){
    distortion_ = (cv::Mat_<float>(4,1)<< distortion(0,0),
            distortion(1,0), distortion(2,0), distortion(3,0));
    K0_  = (cv::Mat_<float>(3,3) << K(0,0), 0., K(0,2),
            0., K(1,1), K(1,2),
            0., 0., 1.);
    set_zoom_ratio(0.2);
}

cv::Mat FisheyeRectifier::rectify(cv::Mat src) const{
    cv::Mat dst;
    cv::remap(src, dst, map1_, map2_, cv::INTER_LINEAR, cv::BORDER_CONSTANT);
    return dst;
}

void FisheyeRectifier::set_zoom_ratio(double zoom_ratio){
    cv::Mat K = K0_.clone();
    K.at<float>(0,2) = 500.;
    K.at<float>(1,2) = 300.;
    K.at<float>(0,0) *= zoom_ratio;
    K.at<float>(1,1) *= zoom_ratio;
    cv::fisheye::initUndistortRectifyMap(K0_, distortion_, cv::Mat::eye(3,3,CV_32F),
            K, cv::Size(1000,600), CV_32FC1, map1_, map2_);
}

Eigen::Matrix<real,2,1> FisheyeIntrinsic::distort(const Eigen::Matrix<real,2,1>& xbar) const {
    const real& k1 = distortion_[0];
    const real& k2 = distortion_[1];
    const real& k3 = distortion_[2];
    const real& k4 = distortion_[3];
	real x0 = std::sqrt(std::pow(xbar[0], 2) + std::pow(xbar[1], 2));
	real x1 = std::atan(x0);
	real x2 = x1*(k1*std::pow(x1, 2.) + k2*std::pow(x1, 4.) + k3*std::pow(x1, 6.) + k4*std::pow(x1, 8.) + 1.0)/x0;
	real xd = xbar[0]*x2; //output[0][0]
	real yd = x2*xbar[1]; //output[1][0]
    return Eigen::Matrix<real,2,1>(xd,yd);
}

Eigen::Matrix<real,2,2> FisheyeIntrinsic::jac_dxtilde_dxbar(const Eigen::Matrix<real,2,1>& xbar) const{
    const real& k1 = distortion_[0];
    const real& k2 = distortion_[1];
    const real& k3 = distortion_[2];
    const real& k4 = distortion_[3];
	real x0 = std::pow(xbar[0], 2.);
	real x1 = std::pow(xbar[1], 2.);
	real x2 = x0 + x1;
	real x3 = std::sqrt(x2);
	real x4 = 1.0/x3;
	real x5 = atan(x3);
	real x6 = k1*std::pow(x5, 2.) + k2*std::pow(x5, 4.) + k3*std::pow(x5, 6.) + k4*std::pow(x5, 8.) + 1.0;
	real x7 = x4*x5*x6;
	real x8 = 1.0/(x2 + 1.);
	real x9 = x6*x8/x2;
	real x10 = x5*x6/std::pow(x2, 3./2.);
	real x11 = xbar[0]*x4*x5;
	real x12 = 2.*k1*x4*x5*x8;
	real x13 = 4.*k2*x4*std::pow(x5, 3.)*x8;
	real x14 = 6.*k3*x4*std::pow(x5, 5.)*x8;
	real x15 = 8.*k4*x4*std::pow(x5, 7.)*x8;
	real x16 = xbar[0]*x12 + xbar[0]*x13 + xbar[0]*x14 + xbar[0]*x15;
	real x17 = x12*xbar[1] + x13*xbar[1] + x14*xbar[1] + x15*xbar[1];
	real x18 = xbar[0]*xbar[1];
	real x19 = -x10*x18 + x18*x9;
	real x20 = x4*x5*xbar[1];
    real t00 = -x0*x10 + x0*x9 + x11*x16 + x7; //output[0][0]
	real t01 = x11*x17 + x19; //output[0][1]
	real t10 = x16*x20 + x19; //output[1][0]
	real t11 = -x1*x10 + x1*x9 + x17*x20 + x7; //output[1][1]
    Eigen::Matrix<real,2,2> jac;
#if 1
    jac << t00, t01, t10, t11;
#else
    jac.setIdentity();
#endif
    return jac;
}

Eigen::Matrix<real,2,1> FisheyeIntrinsic::undistort(const Eigen::Matrix<real,2,1>& xd) const{
    // thanks for opencv source code, cv::fisheye::undistortPoints
    real scale = 1.0;
    real theta_d = std::sqrt(xd[0]*xd[0] + xd[1]*xd[1]);
    if (theta_d > 1e-8) {
        // compensate distortion iteratively
        real theta = theta_d;
        for(int j = 0; j < 10; j++ ) {
            real theta2 = theta*theta;
            real theta4 = theta2*theta2;
            real theta6 = theta4*theta2;
            real theta8 = theta6*theta2;
            theta = theta_d / (1. + distortion_[0] * theta2 + distortion_[1] * theta4 + distortion_[2] * theta6 + distortion_[3] * theta8);
        }
        scale = std::tan(theta) / theta_d;
    }
    return xd * scale; //undistorted point
}

void distortion_test(){
#if 1
    Eigen::Matrix<real,3,3> K;
    K << 219.69993,  0.00000,  323.90130,
       0.00000,  218.98447,  225.92588,
       0.00000,  0.00000,  1.00000;
    Eigen::Matrix<real, 4,1> D;
    D << -0.01982,  -0.00676,  0.00599,  -0.00226;
    cv::Mat cv_K = (cv::Mat_<double>(3,3) <<
            K(0,0), K(0,1), K(0,2),
            K(1,0), K(1,1), K(1,2),
            K(2,0), K(2,1), K(2,2) );
    cv::Mat cv_D = (cv::Mat_<double>(4,1) << D[0], D[1], D[2], D[3]);
    Intrinsic* intrinsic = new FisheyeIntrinsic(K,D);
    //Eigen::Matrix<real,2,1> uv(30, 40); // failure
    Eigen::Matrix<real,2,1> uv(100, 120);
    auto xbar = intrinsic->unproj(uv);
    std::cout << "xbar_hat1 = " << xbar.transpose() << std::endl;
    std::vector<cv::Point2d> pts_i_uv = {cv::Point2d(uv[0],uv[1]), };
    std::vector<cv::Point2d> pts_o_xbar;
    cv::fisheye::undistortPoints(pts_i_uv, pts_o_xbar, cv_K, cv_D);
    std::cout << "xbar_hat2 = " << pts_o_xbar.at(0) << std::endl;
    real z = 1.;
    Eigen::Matrix<real,3,1> Xc(z*xbar[0], z*xbar[1], z);
    std::cout << "uv_true = " << uv.transpose() << std::endl;
    auto uv_hat = intrinsic->proj(Xc);
    std::cout << "uv_hat1 = " << uv_hat.transpose() << std::endl;
    cv::Point3d cv_Xc = cv::Point3d(Xc[0], Xc[1], Xc[2]);
    std::vector<cv::Point3d> pts_i_Xc = {cv_Xc, };
    std::vector<cv::Point2d> pts_o_uv;
    cv::fisheye::projectPoints(pts_i_Xc, pts_o_uv,
            cv::Vec3d::zeros(), cv::Vec3d::zeros(),
            cv_K, cv_D);
    std::cout << "uv_hat2 = " << pts_o_uv.at(0) << std::endl;
#else
    Eigen::Matrix<real,3,3> K;
    K << 226.29111, 0., 324.16461, 0., 221.78938, 226.75197, 0., 0., 1.;
    Eigen::Matrix<real, 4,1> distortion;
    distortion << -0.019787936, 0.011688315, -0.008066264, 0.0017575786;

    Intrinsic* intrinsic = new RadTanIntrinsic(K, distortion);
    Eigen::Matrix<real,2,1> uv(200, 400);
    auto n_uv = intrinsic->unproj(uv);
    real z = 34.;
    Eigen::Matrix<real,3,1> Xc(z*n_uv[0], z*n_uv[1], z);
    auto uv_hat = intrinsic->proj(Xc);
    std::cout << "n_uv = " << n_uv.transpose() << std::endl;
    std::cout << "uv_hat = " << uv_hat.transpose() << std::endl;
    cv::Mat cv_K = (cv::Mat_<float>(3,3) << K(0,0), K(0,1), K(0,2),
            K(1,0), K(1,1), K(1,2),
            K(2,0), K(2,1), K(2,2) );
    cv::Mat cv_dist = (cv::Mat_<float>(4,1) << distortion[0], distortion[1],distortion[2],distortion[3]);
    std::vector<cv::Point2f> pts_i = {cv::Point2f(uv[0], uv[1]), };
    std::vector<cv::Point2f> pts_o;
    cv::undistortPoints(pts_i, pts_o, cv_K, cv_dist);
    std::cout << pts_o[0] << std::endl;
    cv::vector<cv::Point3f> pts_i_Xc = {cv::Point3f(Xc[0], Xc[1], Xc[2]), };
    pts_o.clear();
    cv::projectPoints(pts_i_Xc, cv::Vec3f::zeros(), cv::Vec3f::zeros(), cv_K, cv_dist, pts_o);
    std::cout << pts_o[0] << std::endl;
#endif
}


