#include "direct.h"

namespace test{
class Edge;
class Graph;

class Node{
 public:
  Node() : fixed_(false), marginalized_(false) {
  }

  const std::set<Edge*>& edges() const { return edges_; }
  void addEdge(Edge* edge) { edges_.insert(edge); }
  void eraseEdge(Edge* edge) { edges_.erase(edge); }

  bool fix()const { return fixed_; }
  void set_fix(){ fixed_ = true; }
  bool marginalized()const { return marginalized_; }
  void set_marginalized(Graph* graph);
  virtual ~Node();
 protected:
  // can't oplus, can be referenced by edge for cost computation.
  bool fixed_;
  // can't oplus, can't be referenced for cost computation.
  // only can be referenced for value.
  bool marginalized_;
  std::set<test::Edge*> edges_;
};

class Edge{
 public:
  const std::set<Node*>& nodes() const { return nodes_; }
  std::set<Node*>& nodes() { return nodes_; }
  Edge(){
    printf("create edge\n");
  }

  void expire(){
    for(auto it = nodes_.begin(); it != nodes_.end(); it++){
      Node* node = *it;
      node->eraseEdge(this);
    }
    nodes_.clear();
  }

  virtual ~Edge(){
    printf("destroy edge\n");
  }

 private:
  // fixed node는 포함해도 문제 없음
  // marginalized node는 포함할 수 없다.
  std::set<Node*> nodes_;
};

Node::~Node(){
}

class Graph{
  // Contain non marginalized nodes only.
 public:
  void marginalize(Node* node){
    if(corelated_nodes_.count(node)){
      // TODO : process to reinforce covariance, jacobian residuals
      corelated_nodes_.erase(node);
    }
    else if(independent_nodes_.count(node)){
      // TODO : process to reinforce covariance, jacobian residuals
      independent_nodes_.erase(node);
    }
    else{
      printf("Graph : shared ptr for given node\n");
      throw 1;
    }
    const auto cp_edges = node->edges();
    for(auto it = cp_edges.begin(); it != cp_edges.end(); it++){
      Edge* e = *it;
      e->expire();
      delete e;
    }
  }

  void addCorelated(std::shared_ptr<Node> node){
    if(corelated_nodes_.count(node.get())){
      printf("Graph::addCorelated() can't add exist node\n");
      throw 1;
    }
    corelated_nodes_[node.get()] = node;
  }

  void addIndependent(std::shared_ptr<Node> node){
    if(independent_nodes_.count(node.get())){
      printf("Graph::addIndependent() can't add exist node\n");
      throw 1;
    }
    independent_nodes_[node.get()] = node;
  }

 private:
  // example - motion
  std::map<Node*, std::shared_ptr<Node> > corelated_nodes_;
  // example - sturcture, depth.
  std::map<Node*, std::shared_ptr<Node> > independent_nodes_;

};

void Node::set_marginalized(Graph* graph) {
  graph->marginalize(this);
  marginalized_ = true;
}

// Examples
// Node는 shared_ptr로만 생성을 제한, 메모리 해제를 자동화.
// edge의 파괴는 Graph class가 margianlize 함수를 통해 관리.

class PoseNode : public Node {
 public:
  static std::shared_ptr<PoseNode> create(){
    return std::shared_ptr<PoseNode>(new PoseNode());
  }

 private:
  PoseNode() : Node()
  {
  }
};

class PointNode : public Node {
  // It share pose node as a anchor.
 public:
  static std::shared_ptr<PointNode> create(std::shared_ptr<PoseNode> pose0){
    return std::shared_ptr<PointNode>(new PointNode(pose0));
  }

  const PoseNode* pose0() const { return pose0_.get(); }

 private:
  PointNode(std::shared_ptr<const PoseNode> pose0)
      : Node(),
        pose0_(pose0)
  {

  }
       
  const std::shared_ptr<const PoseNode> pose0_;
};

class ProjEdge : public Edge {
 public:
  ProjEdge(PoseNode* pose, PointNode* pt){
    if(pt->pose0() == pose){
      printf("ProjEdge : pose can not be pose0 of point.\n");
      throw 1;
    }
    nodes().insert(pose);
    nodes().insert(pt);
    pose->addEdge(this);
    pt->addEdge(this);
  }
};

class Frame{
  // Non graph element class
  // It share node
 public:
  Frame(std::shared_ptr<const PoseNode> pose)
      : pose_(pose)
  {

  }

  void addPoint(std::shared_ptr<PointNode> point){
    points_[point.get()] = point;
  }

 private:
  const std::shared_ptr<const PoseNode> pose_;
  std::map<PointNode*, std::shared_ptr<PointNode> > points_;
};


}

void graph_test(){
  using namespace test;
  printf("graph_test()\n");
  Graph graph;
  auto pose0 = PoseNode::create();
  auto pose1 = PoseNode::create();
  auto pose2 = PoseNode::create();

  graph.addCorelated(pose0);
  graph.addCorelated(pose1);
  graph.addCorelated(pose2);

  printf("Before create frame0, n(pose0) = %ld\n", pose0.use_count());
  test::Frame* frame0 = new test::Frame(pose0);
  test::Frame* frame1 = new test::Frame(pose1);
  printf("After create frame0, n(pose0) = %ld\n", pose0.use_count());

  auto pt = PointNode::create(pose0);
  frame0->addPoint(pt);
  frame1->addPoint(pt);
  auto e1 = new test::ProjEdge(pose1.get(), pt.get());
  auto e2 = new test::ProjEdge(pose2.get(), pt.get());
  printf("Before margianlize pose1, n(pose1) = %ld\n", pose1.use_count());
  graph.marginalize(pose1.get());
  printf("After margianlize pose1, n(pose1) = %ld\n", pose1.use_count());

  printf("Before erase frame0,frame1. n(pt) = %ld\n", pt.use_count());
  delete frame0;
  printf("After erase frame0, n(pt) = %ld\n", pt.use_count());
  delete frame1;
  printf("After erase frame1, n(pt) = %ld\n", pt.use_count());

  return;
}
