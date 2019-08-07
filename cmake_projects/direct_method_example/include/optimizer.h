#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_
#include "stdafx.h"

template<typename T> 
Eigen::Matrix<T,3,3> skew(const Eigen::Matrix<T,3,1>& x){
  Eigen::Matrix<T,3,3> m;
  m << 0., -x[2], x[1],
      x[2], 0., -x[0],
      -x[1], x[0], 0.;
  return m;
}

template <typename T> class OptEdge;

template <typename T>
class OptNode{
 public:
  OptNode() : fix_(false) { n_instance_++; }
  virtual ~ OptNode();
  virtual size_t dim()const  = 0;
  virtual void oplus(const Eigen::Matrix<T,-1,1>& dx) = 0;

  bool fixed()const { return fix_; } // 계산에서 무시
  void fix(bool fix) { fix_ = fix; }
  void addEdge(OptEdge<T>* e) {  edges_.insert(e); }
  void removeEdge(OptEdge<T>* e);

  const std::set<OptEdge<T>*>& edges() const{ return edges_; }
  static int n_instance(){ return n_instance_; }
  static void set_print_create_destruct(bool verbose) { print_create_destruct_ = verbose; }
  static bool print_create_destruct() { return print_create_destruct_; }
 private:
  bool fix_;
  std::set<OptEdge<T>*> edges_;
  static int n_instance_;
  static bool print_create_destruct_;
};



template <typename T>
class OptEdge{
  // 1~N 개의 node를 연결하는 edge
 public:
  enum Type{F2F, F2P, P};

  OptEdge() { n_instance_++; }
  virtual ~ OptEdge();
  void expire(){
    for(auto it = nodes_.begin(); it != nodes_.end(); it++){
      OptNode<T>* node = *it;
      node->removeEdge(this);
    }
    nodes_.clear();
  }
  bool expired()const { return nodes_.size() > 0; }
  virtual OptEdge<T>::Type type()const = 0;
  virtual Eigen::Matrix<T,-1,1> error() const = 0;
  virtual const VectorVectorX<T>& jres() const = 0;
  virtual const VectorMatrixX<T>& hessians() const = 0;
  virtual const std::vector<std::pair<OptNode<T>*, OptNode<T>*> >& hessians_domain() const = 0;
  // Hessian은 n! 조합이 나와야함.
  virtual void update() = 0; // update hessian, jres

  static void classify(OptEdge<T>* edge,
                       std::set<OptEdge*>& ff_edges,
                       std::set<OptEdge*>& fp_edges,
                       std::set<OptEdge*>& p_edges);

  const std::vector<OptNode<T>*>& nodes()const { return nodes_; }
  std::vector<OptNode<T>*>& nodes() { return nodes_; }
  static int n_instance(){ return n_instance_; }
  static void set_print_create_destruct(bool verbose) { print_create_destruct_ = verbose; }
  static bool print_create_destruct() { return print_create_destruct_; }

 protected:
  static int n_instance_;
  static bool print_create_destruct_;
  std::vector<OptNode<T>*> nodes_; // jacobians와 순서를 같게
  // F2P는 Frame, Point 순서로
};

template<typename T>
class OptMarginals{
 public:
  virtual void marginalize_frame(OptNode<T>* frame, bool delete_edges) = 0;
  virtual void marginalize_point(OptNode<T>* pt, bool delete_edges) = 0;
  virtual const std::map<std::pair<OptNode<T>*, OptNode<T>*>,
                         Eigen::Matrix<T,-1,-1>, std::less< std::pair<OptNode<T>*, OptNode<T>*> >,
                         Eigen::aligned_allocator<std::pair<std::pair<OptNode<T>*, OptNode<T>*>, Eigen::Matrix<T,-1,-1> > > > &
  hessians() const = 0;
  virtual const std::map<OptNode<T>*, Eigen::Matrix<T,-1,1>, std::less<OptNode<T>*>,
                         Eigen::aligned_allocator<std::pair<OptNode<T>*, Eigen::Matrix<T,-1,1> > > > & jres() const = 0;

 protected:
};

template<typename T>
class OptInfo{
 public:
  size_t iter_;
  T chi2_;
  const Eigen::Matrix<T,-1,-1>* Ha_;
  const Eigen::Matrix<T,-1,-1>* Hb_;
  const std::map<OptNode<T>*, int> *rj_, *ri_;
  std::set<OptEdge<T>*> *ff_edges_, *fp_edges_, *p_edges_;
  bool error_;
  OptInfo(): Ha_(NULL), Hb_(NULL), ri_(NULL), rj_(NULL),
             ff_edges_(NULL), fp_edges_(NULL), p_edges_(NULL)
  {
  }
};

// TODO interface가 아니라 Observer?
template<typename T>
class OptInterface{
 public:
  virtual void on_update(const OptInfo<T>& info){
    printf("iter, chi2 = %3ld, %e\n", info.iter_, info.chi2_);
  }
 private:
};


#include "optimizer.hpp"

void optimizer_test();


#endif
