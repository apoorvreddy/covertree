#include "covertree.h"

CoverTree::CoverTree() {
  base = 2;
  maxLevel = 5;
  minLevel = maxLevel - 1;
  root = nullptr;
}

CoverTree::~CoverTree() {
  std::cout << "Deleting covertree\n";
}

void CoverTree::insertPoint(Point& point) {
  if(root == nullptr) {
    root = new Node(point, maxLevel);
  } else {
    Node *node = new Node(point);
    std::vector<Node*> qi; 
    qi.push_back(root);
    insertNode(node, qi, maxLevel);
  }
}

bool CoverTree::insertNode(Node* node, std::vector<Node*> coverset_qi, int level) {

  std::vector<Node*> coverset_q;
  for (Node* n: coverset_qi) {
    std::vector<Node*> nChildren = n->getChildren();
    if (nChildren.empty()){
      Node *selfchild = new Node(n->getPoint(), n->getLevel() - 1);
      n->addChild(selfchild);
      if (selfchild->getLevel() < minLevel)
        minLevel = selfchild->getLevel();
    }
    for (auto e: n->getChildren()) {
      coverset_q.push_back(e);
    }
    // Why doesn't the following work ! :(
    // coverset_q.insert(coverset_q.begin(), n->getChildren().begin(), n->getChildren().end());
  }
  double minDist_q = node->getMinDist(coverset_q);
  if (minDist_q > pow(base, level))
    return false;
  else {
    std::vector<Node*> coverset_qi_1;

    for (Node* n: coverset_q) {
      if (node->getDistance(n) <= pow(base, level)) {
        coverset_qi_1.push_back(n);
      }
    }

    double minDist_qi = node->getMinDist(coverset_qi);
    bool inserted = insertNode(node, coverset_qi_1, level-1);
    if (inserted)
      return true;
    else if (!inserted && minDist_qi <= pow(base, level)) {
      for (Node* n: coverset_qi) {
        if (node->getDistance(n) <= pow(base, level)) {
          node->setLevel(level - 1);
          n->addChild(node);
          break;
        }
      }
      if (level < minLevel)
        minLevel = level;
      return true;
    } else return false;
  }
}

Point& CoverTree::nearestNeighbour(Point& point) {

  int i = maxLevel;
  NodeSet qi, q, qi_1;
  qi.insert(root);
  while(i>minLevel) {
    for(Node* node: qi)
      for(Node* nodeChild: node->getChildren())
        q.insert(nodeChild);
      // q.insert(node->getChildren().begin(), node->getChildren().end()); Why doesn't this work !!

    std::pair<double, Node*> distNodePair = getMinDistNodeSet(point, q);
    double threshold = distNodePair.first + pow(base, i);

    for(Node *node: q) {
      if (point.distance(node->getPoint()) <= threshold)
        qi_1.insert(node);
    }
    qi = qi_1;
    i--;
  }
  std::pair<double, Node*> distNodePair = getMinDistNodeSet(point, qi_1);
  Point p = distNodePair.second->getPoint();
  return p;
}


void CoverTree::print() {
  std::queue<Node*> tempBuffer;
  std::cout << "======CoverTree=====\n";
  std::cout << "maxLevel " << maxLevel << " minLevel " << minLevel << "\n";
  int i = maxLevel;
  std::cout << "Level " << i << ": ";
  tempBuffer.push(root);
  while (!tempBuffer.empty()) {
    Node *n = tempBuffer.front();
    if (n->getLevel() != i) {
      std::cout << "\n";
      i--;
      std::cout << "Level " << i << ": "; 
    }
    std::cout << n->getPoint().getId() << ":" << n->getLevel() << " ";
    tempBuffer.pop();
    for (Node *child: n->getChildren()) {
      tempBuffer.push(child);
    }
  }
  std::cout << "\n============\n";
}