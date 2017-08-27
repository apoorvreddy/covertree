#ifndef COVERTREE_COVERTREE_H
#define COVERTREE_COVERTREE_H

#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
#include "point.h"
#include "node.h"

class CoverTree {
private:
  float base;
  int maxLevel;
  int minLevel;
  Node* root;

  bool insertNode(Node* node, std::vector<Node*> coverset_qi, int level);

public:

  CoverTree();
  ~CoverTree();

  void batchInsert(std::vector<Point> &points);
  void insertPoint(Point& point);
  void print();
  Point& nearestNeighbour(Point& point);
  std::vector<Point>& kNN(Point& point);
  Point& epsilonNearestNeighbour(Point& point);

};

#endif  // COVERTREE_COVERTREE_H