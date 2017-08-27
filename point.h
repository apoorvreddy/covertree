#ifndef COVERTREE_POINT_H
#define COVERTREE_POINT_H

#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>

class Point {
private:
  std::vector<double> vec;
  std::string id;
public:
  std::vector<double> getVec() const;
  std::string getId() const;
  double distance(const Point &p1) const;
  double operator[](int i) const;
  bool operator==(const Point &p1) const;
  void set(std::string k, std::vector<double> v);
  void print() const;
};

#endif  // COVERTREE_POINT_H