#include "utils.h"

// stackoverflow link: http://bit.ly/2i6sN4w
template <typename T>
std::vector<T> split(const std::string& line) {
  std::istringstream is(line);
  return std::vector<T>(std::istream_iterator<T>(is),
    std::istream_iterator<T>());
}

std::vector<Point> load_data(char* filename) {
  std::vector<Point> pv;
  std::ifstream is(filename);
  std::string line;
  std::string delimiter = " ";
  while (std::getline(is, line)) {
    int pos = line.find(delimiter);
    std::string id = line.substr(0, pos);
    Point p;
    p.set(id, split<double>(line.substr(pos+1)));
    pv.push_back(p);
  }
  return pv;
}