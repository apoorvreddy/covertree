#include "node.h"

Point Node::getPoint() {return point;}

int Node::getLevel() {return level;}

void Node::setLevel(int l) {level = l;}

std::vector<Node*> Node::getChildren() {return children;}

void Node::addChild(Node *n) {
  children.push_back(n);
}

Node::~Node() {
  std::cout << "Deleting node " << this << "\n";
  std::vector<Node*> tempBuffer;
  tempBuffer.insert(tempBuffer.begin(), children.begin(), children.end());
  while(!tempBuffer.empty()) {
    Node *tempNode = tempBuffer[0];
    std::vector<Node*> tempNodeChildren = tempNode->getChildren();
    tempBuffer.erase(tempBuffer.begin());
    tempBuffer.insert(tempBuffer.end(), tempNodeChildren.begin(), tempNodeChildren.end());
    delete tempNode;
  }
}

double Node::getDistance(Node* node) {
  return point.distance(node->point);
}

double Node::getMinDist(std::vector<Node*> nodeList) {
  double minDist = std::numeric_limits<double>::max();
  for (Node* n: nodeList) {
    double d = getDistance(n);
    if (minDist > d) {
      minDist = d;
    }
  }
  return minDist;
}

bool Node::operator==(const Node& otherNode) const {
  return point == otherNode.point;
}

std::size_t NodeHash::operator()(Node* node) const {
  std::hash<std::string> hashString;
  return hashString(node->getPoint().getId());
}

std::pair<double, Node*> getMinDistNodeSet(const Point& p, const NodeSet& ns) {
  double minDist = std::numeric_limits<double>::max();
  Node* argminNode;
  for (Node *n: ns) {
    double d = p.distance(n->getPoint());
    if (minDist > d) {
      minDist = d;
      argminNode = n;
    }
  }
  return std::make_pair(minDist, argminNode);
}