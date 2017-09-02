#ifndef COVERTREE_NODE_H
#define COVERTREE_NODE_H

#include <vector>
#include <limits>
#include <unordered_set>
#include <queue>
#include <utility>
#include "point.h"


class Node {
private:
  Point point;
  int level;
  std::vector<Node*> children;
public:
  Node(Point p) {
    point = p; 
  }

  Node(Point p, int l) {
    point = p;
    level = l;
  }

  ~Node();

  Point getPoint();
  std::vector<Node*> getChildren();
  int getLevel();
  void setLevel(int l);
  void addChild(Node *n);
  double getDistance(Node* node);
  double getMinDist(std::vector<Node*> nodeList);
  bool hasChildren();
  bool operator==(const Node& otherNode) const;
};


class NodeHash{
public:
  std::size_t operator()(Node* node) const;
};

class DistanceNodeComparator{
public:
  bool operator()(std::pair<double, Node*>, std::pair<double, Node*>) const;
};

typedef std::unordered_set<Node*, NodeHash> NodeSet;
typedef std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, DistanceNodeComparator> NodeDistPriorityQ;
std::pair<double, Node*> getMinDistNodeSet(const Point& p, const NodeSet& ns);
NodeDistPriorityQ getDistNodeSet(const Point& p, const NodeSet& ns);

#endif  // COVERTREE_NODE_H