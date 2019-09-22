#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <iostream>
#include <stdint.h>

#include <unordered_set>

#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/optimizable_graph.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/solver.h>
#include <g2o/core/robust_kernel_impl.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <g2o/types/slam3d/types_slam3d.h>
#include <g2o/types/slam3d_addons/types_slam3d_addons.h>
#include <g2o/solvers/structure_only/structure_only_solver.h>
// #include <g2o/solvers/cholmod/linear_solver_cholmod.h>
// #include <g2o/solvers/csparse/linear_solver_csparse.h>

using namespace Eigen;
using namespace std;

class Sample {
 public:
  static int uniform(int from, int to);
  static double uniform();
  static double gaussian(double sigma);
};

static double uniform_rand(double lowerBndr, double upperBndr){
  return lowerBndr + ((double) std::rand() / (RAND_MAX + 1.0)) * (upperBndr - lowerBndr);
}

static double gauss_rand(double mean, double sigma){
  double x, y, r2;
  do {
    x = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    y = -1.0 + 2.0 * uniform_rand(0.0, 1.0);
    r2 = x * x + y * y;
  } while (r2 > 1.0 || r2 == 0.0);
  return mean + sigma * y * std::sqrt(-2.0 * log(r2) / r2);
}

int Sample::uniform(int from, int to){
  return static_cast<int>(uniform_rand(from, to));
}

double Sample::uniform(){
  return uniform_rand(0., 1.);
}

double Sample::gaussian(double sigma){
  return gauss_rand(0., sigma);
}

int main(int argc, const char* argv[]){
  std::unique_ptr<g2o::BlockSolver_6_3::LinearSolverType> linearSolver;
  linearSolver = g2o::make_unique<g2o::LinearSolverDense<g2o::BlockSolver_6_3::PoseMatrixType>>();

  g2o::OptimizationAlgorithmLevenberg* solver = new g2o::OptimizationAlgorithmLevenberg(
      g2o::make_unique<g2o::BlockSolver_6_3>(std::move(linearSolver)));
  
  g2o::SparseOptimizer* optimizer = new g2o::SparseOptimizer();
  optimizer->setVerbose(true);
  optimizer->setAlgorithm(solver);

  vector<Eigen::Isometry3d, aligned_allocator<Eigen::Isometry3d>> true_poses;
  int vertex_id=0;

  for(size_t i=0; i<5; i++){
    Vector3d trans(i*0.04-1, 0 ,0);
    Eigen::Quaterniond q;
    q.setIdentity();

    Eigen::Isometry3d pose;
    pose.setIdentity();
    pose.linear() = q.toRotationMatrix();
    pose.translation() = trans;

    g2o::VertexSE3* v_se3 = new g2o::VertexSE3();
    v_se3->setId(vertex_id);

    if(i==0){
      v_se3->setFixed(true);
    }

    v_se3->setEstimate(pose);
    optimizer->addVertex(v_se3);

    true_poses.push_back(pose);
    vertex_id += 1;
  }

  for(int i=1;i<true_poses.size();i++){
    g2o::EdgeSE3* e_se3(new g2o::EdgeSE3());
    Eigen::Isometry3d relative_pose = true_poses.at(i-1).inverse() * true_poses.at(i);

    e_se3->setMeasurement(relative_pose);
    e_se3->setInformation(Eigen::MatrixXd::Identity(6,6));
    e_se3->vertices()[0] = optimizer->vertex(i-1);
    e_se3->vertices()[1] = optimizer->vertex(i);
    optimizer->addEdge(e_se3);
  }

  optimizer->initializeOptimization();
  optimizer->setVerbose(true);
  optimizer->optimize(10);
}
