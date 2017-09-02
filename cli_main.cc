#include <iostream>
#include "utils.h"
#include "point.h"
#include "covertree.h"

int main(int argc, char *argv[]) {

  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <train_file> <test_file>" << std::endl;
    return 1;
  }

  std::cout << "Train File: " << argv[1] << ", Test File: " << argv[2] << "\n";
  std::vector<Point> pv = load_data(argv[1]);

  std::cout << "Training Points\n";
  CoverTree covertree;
  for (Point e: pv) {
    covertree.insertPoint(e);
    e.print();
  }

  covertree.print();

  std::vector<Point> pt = load_data(argv[2]);
  for (Point e: pt) {
    std::pair<double, Point> nearest = covertree.nearestNeighbour(e);
    e.print();
    std::cout << "Nearest neighbour for " << e.getId() << " is point " << nearest.second.getId() << " with distance " << nearest.first << "\n";
  }

  for (Point e: pt) {
    std::vector<std::pair<double, Point>> knn = covertree.kNN(e, 2);
    e.print();
    std::cout << "kNN ";
    for (std::pair<double, Point> p: knn) {
      std::cout << "(" << p.second.getId() << ", " << p.first << "); ";
    }
    std::cout << "\n";
  }

  return 0;
}