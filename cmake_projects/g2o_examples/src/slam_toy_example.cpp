#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <iostream>
#include <stdint.h>

#include <unordered_set>

#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/solver.h>
#include <g2o/core/robust_kernel_impl.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
// #include <g2o/solvers/cholmod/linear_solver_cholmod.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <g2o/types/sba/types_six_dof_expmap.h>
#include <g2o/types/slam3d/se3quat.h>
#include <g2o/types/slam3d/vertex_se3.h>
#include <g2o/types/slam3d/edge_se3.h>
#include <g2o/solvers/structure_only/structure_only_solver.h>

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
  
  g2o::SparseOptimizer optimizer;
  optimizer.setVerbose(true);
  optimizer.setAlgorithm(solver);

  vector<g2o::SE3Quat, aligned_allocator<g2o::SE3Quat>> true_poses;
  cout << "debug01" << endl;  // ed: DEBUG

  int vertex_id=0;


  for(size_t i=0; i<5; i++){
    Vector3d trans(i*0.04-1, 0 ,0);
    Eigen::Quaterniond q;
    q.setIdentity();
  cout << "debug2" << endl;  // ed: DEBUG

    g2o::SE3Quat pose(q, trans);
    g2o::SE3Quat prev_pose;
    g2o::VertexSE3* prev_v_se3 = new g2o::VertexSE3();
    g2o::VertexSE3* v_se3 = new g2o::VertexSE3();
    v_se3->setId(vertex_id);

  cout << "debug3" << endl;  // ed: DEBUG
    if(i==1){
      v_se3->setFixed(true);
    }

    v_se3->setEstimate(pose);
    optimizer.addVertex(v_se3);
    true_poses.push_back(pose);

  cout << "debug4" << endl;  // ed: DEBUG
    if(i>=2) {
      prev_v_se3->setEstimate(prev_pose);

      g2o::SE3Quat relative_pose = pose.inverse() * prev_pose;

  cout << "debug5" << endl;  // ed: DEBUG
      g2o::EdgeSE3* e_se3 = new g2o::EdgeSE3;
      e_se3->setMeasurement(relative_pose);
      // e_se3->setInformation(Eigen::Matrix3d::Identity());
      e_se3->setVertex(0, dynamic_cast<g2o::OptimizableGraph::Vertex*>(prev_v_se3));
      e_se3->setVertex(1, dynamic_cast<g2o::OptimizableGraph::Vertex*>(v_se3));
      optimizer.addEdge(e_se3);
  cout << "debug6" << endl;  // ed: DEBUG
    }
    prev_pose = pose;
    vertex_id += 1;
  }

  optimizer.initializeOptimization();
  optimizer.setVerbose(true);
  optimizer.optimize(10);

}
