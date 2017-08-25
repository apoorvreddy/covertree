#include "covertree.h"

CoverTree::CoverTree() {
  base = 1.3;
  maxLevel = 10;
  minLevel = maxLevel - 1;
  root = nullptr;
}

void CoverTree::insertPoint(Point& point) {
  if(root == nullptr) {
    pointSet.push_back(point);
    root = new Node(&point, maxLevel);
  } else {
    Node *node = new Node(&point);
    std::vector<Node*> qi; qi.push_back(root);
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
    }
    coverset_q.insert(coverset_q.end(), n->getChildren().begin(), n->getChildren().end());
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
    if (!insertNode(node, coverset_qi_1, level - 1) && minDist_qi <= pow(base, level)) {
      for (Node* n: coverset_q) {
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

