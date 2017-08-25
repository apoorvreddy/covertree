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
  for (auto e: pv) {
    e.print();
  }

  CoverTree covertree;
  for  (auto e: pv) {
    covertree.insertPoint(e);
  }


  return 0;
}