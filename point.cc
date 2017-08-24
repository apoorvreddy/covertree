#include "point.h"

std::vector<double> Point::getVec() const {return vec;}

double Point::operator[](int i) const {return vec[i];}

bool Point::operator==(const Point &p) const {return vec==p.getVec();}

void Point::set(std::string k, std::vector<double> v) {id=k; vec=v;}

void Point::print() const {
  std::cout << "id:" << id << " ";
  for (auto e: vec) {
    std::cout << " " << e;
  }
  std::cout << "\n";
}

double Point::distance(const Point &p) const {
  assert(vec.size() == p.getVec().size());
  double sum = 0, x;
  for (int i=0; i<vec.size(); i++) {
    x = vec[i] - p[i];
    sum += x*x;
  }
  return sqrt(sum);
}