#ifndef COVERTREE_COVERTREE_H
#define COVERTREE_COVERTREE_H

#include <cmath>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
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
  std::pair<double, Point> nearestNeighbour(Point& point);
  std::vector<std::pair<double, Point>> kNN(Point& point, int k);
  Point& epsilonNearestNeighbour(Point& point);

};

#endif  // COVERTREE_COVERTREE_H