#ifndef COVERTREE_COVERTREE_H
#define COVERTREE_COVERTREE_H

#include <cmath>
#include <vector>
#include "point.h"
#include "node.h"

class CoverTree {
private:
  float base;
  int maxLevel;
  int minLevel;
  Node* root;
  std::vector<Point> pointSet;

  bool insertNode(Node* node, std::vector<Node*> coverset_qi, int level);

public:

  CoverTree();
  // ~CoverTree();

  void batchInsert(std::vector<Point> &points);
  void insertPoint(Point& point);
  Point& nearestNeighbour(Point& point);
  std::vector<Point>& kNN(Point& point);
  Point& epsilonNearestNeighbour(Point& point);

};

#endif  // COVERTREE_COVERTREE_H