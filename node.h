#ifndef COVERTREE_NODE_H
#define COVERTREE_NODE_H

#include <vector>
#include <limits>
#include "point.h"

class Node {
private:
  Point* point;
  int level;
  std::vector<Node*> children;
public:
  Node(Point* p) {
    point = p; 
  }

  Node(Point* p, int l) {
    point = p;
    level = l;
  }

  ~Node();

  Point* getPoint();
  std::vector<Node*> getChildren();
  int getLevel();
  void setLevel(int l);
  void addChild(Node *n);
  double getDistance(Node* node);
  double getMinDist(std::vector<Node*> nodeList);
};

#endif  // COVERTREE_NODE_H