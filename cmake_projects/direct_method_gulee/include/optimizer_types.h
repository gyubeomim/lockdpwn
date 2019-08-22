#ifndef OPTIMIZER_TYPES_H_
#define OPTIMIZER_TYPES_H_

#include "optimizer.h"

template <typename T>
class PoseSE2 : public OptNode<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  PoseSE2(const Sophus::SE2<T>& g_cw);
  virtual ~PoseSE2();
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx){
    g_cw_ =  Sophus::SE2<T>::exp(dx) * g_cw_; // pre/post multiply를 분명하게 정의
    return;
  }
  const Sophus::SE2<T>& g_cw()const { return g_cw_; }
  virtual size_t dim()const{ return 3; }
 private:
  Sophus::SE2<T> g_cw_;
};


template<typename T>
class Point2 : public OptNode<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Point2(PoseSE2<T>* f0, T uv0, T rho);
  virtual ~Point2();
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx);
  const Eigen::Matrix<T,2,1> x0()const { return Eigen::Matrix<T,2,1>(1./ rho_, uv0_ / rho_); }
  const Eigen::Matrix<T,2,1> xw()const { return f0_->g_cw().inverse() * x0(); }
  T invd() const { return rho_; }
  T uv0() const { return uv0_; }
  const PoseSE2<T>* frame0()const { return f0_; }
  size_t dim()const{ return 1;}
 private:
  PoseSE2<T>*const f0_;
  T uv0_;
  T rho_;
};

template<typename T>
class ProjSE2Edge : public OptEdge<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ProjSE2Edge(PoseSE2<T>* f, Point2<T>* pt, T z); // f != f0

  virtual typename OptEdge<T>::Type type() const{ return OptEdge<T>::Type::F2P; }
  static T proj(const Eigen::Matrix<T,2,1>& x_c){ return x_c.y()/ x_c.x(); }
  static T proj(const PoseSE2<T>* f, const Point2<T>* pt){
    const Eigen::Matrix<T,2,1>& x_c = f->g_cw() * pt->xw();
    return ProjSE2Edge::proj(x_c);
  }

  virtual Eigen::Matrix<T,-1,1> error() const;
  virtual void update();
  virtual const VectorVectorX<T>& jres() const { return jres_; }
  virtual const VectorMatrixX<T>& hessians() const { return hessians_; }
  virtual const std::vector<std::pair<OptNode<T>*, OptNode<T>*> >& hessians_domain() const { return hessians_domain_; }

 private:
  const T z_; // tan
  std::vector<std::pair<OptNode<T>*, OptNode<T>*> > hessians_domain_;
  VectorMatrixX<T> hessians_, jacobians_;
  VectorVectorX<T> jres_;
};

template<typename T>
class ProjDisparitySE2Edge : public OptEdge<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ProjDisparitySE2Edge(T* offset, Point2<T>* pt, T z);
  virtual typename OptEdge<T>::Type type() const{ return OptEdge<T>::Type::P; }

  // Definition : disparity
  static T disparity(const Eigen::Matrix<T,2,1>& x0, T offset) { return offset / x0.x(); }
  static T disparity(const Point2<T>* pt, T offset)        { return offset * pt->invd(); }

  virtual Eigen::Matrix<T,-1,1> error() const{
    Point2<T>* pt = static_cast<Point2<T>*>( OptEdge<T>::nodes().at(0));
    T hx = ProjDisparitySE2Edge::disparity(pt, *offset_);
    return Eigen::Matrix<T,1,1>(hx - z_);
  }

  virtual void update();
  virtual const VectorVectorX<T>& jres() const { return jres_; }
  virtual const VectorMatrixX<T>& hessians() const { return hessians_; }
  virtual const std::vector<std::pair<OptNode<T>*, OptNode<T>*> >& hessians_domain() const { return hessians_domain_; }

 private:
  const T*const offset_;
  const T z_;
  std::vector<std::pair<OptNode<T>*, OptNode<T>*> > hessians_domain_;
  VectorMatrixX<T> hessians_, jacobians_;
  VectorVectorX<T> jres_;
};

template<typename T>
class GeneralOptMarginals : public OptMarginals<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  GeneralOptMarginals() { }

  virtual void marginalize_frame(OptNode<T>* frame, bool delete_edges);
  virtual void marginalize_point(OptNode<T>* pt, bool delete_edges);
  virtual const std::map<std::pair<OptNode<T>*, OptNode<T>*>,
                         Eigen::Matrix<T,-1,-1>, std::less< std::pair<OptNode<T>*, OptNode<T>*> >,
                         Eigen::aligned_allocator<std::pair<std::pair<OptNode<T>*, OptNode<T>*>, Eigen::Matrix<T,-1,-1> > > > &
  hessians() const { return dUjk_; }
  virtual const std::map<OptNode<T>*, Eigen::Matrix<T,-1,1>, std::less<OptNode<T>*>,
                         Eigen::aligned_allocator<std::pair<OptNode<T>*, Eigen::Matrix<T,-1,1> > > > & jres() const { return jres_; }

 protected:
  std::map<std::pair<OptNode<T>*, OptNode<T>*>, Eigen::Matrix<T,-1,-1>, std::less< std::pair<OptNode<T>*, OptNode<T>*> >,
           Eigen::aligned_allocator<std::pair<std::pair<OptNode<T>*, OptNode<T>*>, Eigen::Matrix<T,-1,-1> > > > dUjk_;
  // 주의 : jres_에서 frame을 지우면 nodes_에서도 해당 프레임을 찾아 지워야함.
  std::map<OptNode<T>*, Eigen::Matrix<T,-1,1>, std::less<OptNode<T>*>,
           Eigen::aligned_allocator<std::pair<OptNode<T>*, Eigen::Matrix<T,-1,1> > > > jres_;
};

enum ExpMult{ POST, PRE, };

template<typename T>
class PoseSE3 : public OptNode<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  PoseSE3(const Sophus::SE3<T>& g_cw, ExpMult exp_mult);
  virtual ~PoseSE3();
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx){
    //if(dx.block(0,0,6,1).norm() > 0.5)
    //    std::cout << "oplus:\n" << g_cw_.inverse().matrix3x4() << "->\n";
    if(exp_mult_== ExpMult::PRE)
      g_cw_ =  Sophus::SE3<T>::exp(dx) * g_cw_;
    else // For Inverse Compositional method.
      g_cw_ = g_cw_ * Sophus::SE3<T>::exp(-dx);
    //if(dx.block(0,0,6,1).norm() > 0.5)
    //    std::cout << "" << g_cw_.inverse().matrix3x4() << std::endl;
    return;
  }
  const Sophus::SE3<T>& g_cw()const { return g_cw_; }
  //Sophus::SE3<T>& g_cw() { return g_cw_; }
  virtual size_t dim()const{ return 6; }
 protected:
  Sophus::SE3<T> g_cw_;
  const ExpMult exp_mult_;
};


template<typename T>
class Point3 : public OptNode<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  Point3(PoseSE3<T>* f0, const Eigen::Matrix<T,2,1>& n_uv0, T rho) : f0_(f0), n_uv0_(n_uv0), rho_(rho) {
    bool c1 =false;
    if(std::abs(n_uv0.x()) > 20.) c1 = true;
    else if(std::abs(n_uv0.y()) > 20.) c1 = true;
    if(c1){
      printf("Error : strange image for normalized uv\n");
      throw 1;
    }
  }
  virtual ~Point3() { }
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx);
  virtual size_t dim()const{ return 1;}

  Eigen::Matrix<T,3,1> x0()const { return Eigen::Matrix<T,3,1>(n_uv0_.x()/rho_, n_uv0_.y()/rho_, 1./rho_ ); }
  Eigen::Matrix<T,3,1> xw()const { return f0_->g_cw().inverse() * x0(); }
  T invd() const { return rho_; }
  const Eigen::Matrix<T,2,1>& n_uv0() const { return n_uv0_; }
  const PoseSE3<T>* frame0()const { return f0_; }

  void set_depth(T depth){ rho_ = 1./depth; }
 private:
  PoseSE3<T>*const f0_;
  const Eigen::Matrix<T,2,1> n_uv0_;
  T rho_;
};

template<typename T>
class ProjDisparitySE3Edge : public OptEdge<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ProjDisparitySE3Edge(T* offset, Point3<T>* pt, T z);
  virtual typename OptEdge<T>::Type type() const{ return OptEdge<T>::Type::P; }

  // Definition : normalized disparity
  static T disparity(const Eigen::Matrix<T,3,1>& x0, T offset) { return offset / x0.z(); }
  static T disparity(const Point3<T>* pt, T offset)        { return offset * pt->invd(); }

  virtual Eigen::Matrix<T,-1,1> error() const{
    Point3<T>* pt = static_cast<Point3<T>*>( OptEdge<T>::nodes().at(0));
    T hx = ProjDisparitySE3Edge::disparity(pt, *offset_);
    return Eigen::Matrix<T,1,1>(hx - z_);
  }

  virtual void update();
  virtual const VectorVectorX<T>& jres() const { return jres_; }
  virtual const VectorMatrixX<T>& hessians() const { return hessians_; }
  virtual const std::vector<std::pair<OptNode<T>*, OptNode<T>*> >& hessians_domain() const { return hessians_domain_; }

 private:
  const T*const offset_;
  const T z_;
  std::vector<std::pair<OptNode<T>*, OptNode<T>*> > hessians_domain_;
  VectorMatrixX<T> hessians_, jacobians_;
  VectorVectorX<T> jres_;
};

template<typename T>
class ProjSE3Edge : public OptEdge<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  ProjSE3Edge(PoseSE3<T>* f, Point3<T>* pt, const Eigen::Matrix<T,2,1>& z);
  virtual Eigen::Matrix<T,-1,1> error() const;
  virtual void update();

  virtual typename OptEdge<T>::Type type() const{ return OptEdge<T>::Type::F2P; }
  static Eigen::Matrix<T,2,1> proj(const Eigen::Matrix<T,3,1>& x_c){
    return x_c.template head<2>()/x_c.z();
  }
  static Eigen::Matrix<T,2,1> proj(const PoseSE3<T>* f, const Point3<T>* pt){
    const Eigen::Matrix<T,3,1>& x_c = f->g_cw() * pt->xw();
    return ProjSE3Edge::proj(x_c);
  }
  virtual const VectorVectorX<T>& jres() const { return jres_; }
  virtual const VectorMatrixX<T>& hessians() const { return hessians_; }
  virtual const std::vector<std::pair<OptNode<T>*, OptNode<T>*> >& hessians_domain() const { return hessians_domain_; }

 private:
  const Eigen::Matrix<T,2,1> z_; // tan
  std::vector<std::pair<OptNode<T>*, OptNode<T>*> > hessians_domain_;
  VectorMatrixX<T> hessians_, jacobians_;
  VectorVectorX<T> jres_;
};

template<typename T>
class GammaState : public OptNode<T>{
  // Relative gamma correction parameter to left camera
  // Motion parameter of stereo right camera
  // ref : https://docs.opencv.org/3.4/d3/dc1/tutorial_basic_linear_transform.html
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  GammaState(){ gamma_ << 1., 1.; }
  virtual ~GammaState(){
    if(OptNode<T>::print_create_destruct())
      printf("~GammaState() %p\n", this);
  }
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx){ gamma_ += dx; }
  virtual size_t dim()const { return 2; }
 private:
  Eigen::Matrix<T,2,1> gamma_;
};

template<typename T>
class GammaPoseSE3 : public PoseSE3<T>{
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  GammaPoseSE3(const Sophus::SE3<T>& g_cw, ExpMult exp_mult)
      : PoseSE3<T>(g_cw, exp_mult){
    gamma_ << 1., 1.;
  }
  virtual ~GammaPoseSE3(){

  }
  const Eigen::Matrix<T,2,1>& gamma() const { return gamma_; }
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx){
    const auto& se3 = dx.block(0,0,6,1);
    const auto& d_gamma = dx.block(6,0,2,1);
    PoseSE3<T>::oplus(se3);
    if(PoseSE3<T>::exp_mult_== ExpMult::PRE){
      gamma_ += d_gamma;
    }
    else{ // For Inverse Compositional method.
      gamma_ += d_gamma;
    }
    return;
  }
  virtual size_t dim()const{ return 8; }
 private:
  Eigen::Matrix<T,2,1> gamma_;
};

#include "optimizer_types.hpp"

#endif


