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
    if (!n->hasChildren()){
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

std::pair<double, Point> CoverTree::nearestNeighbour(Point& point) {

  int i = maxLevel;
  NodeSet qi, qi_1;
  qi.insert(root);
  while(i>minLevel) {
    NodeSet q;
    qi_1.clear();
    for(Node* node: qi) {
      if (node->hasChildren()) {
        for(Node* nodeChild: node->getChildren())
          q.insert(nodeChild);
      } else {
          Node *selfchild = new Node(node->getPoint(), node->getLevel() - 1);
          node->addChild(selfchild);
          if (selfchild->getLevel() < minLevel)
            minLevel = selfchild->getLevel();
          q.insert(selfchild);
      }
    }

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
  return std::make_pair(distNodePair.first, p);
}

std::vector<std::pair<double, Point>> CoverTree::kNN(Point& point, int k) {

  int i = maxLevel;
  NodeSet qi, qi_1;
  NodeDistPriorityQ distNodePQ;
  double threshold;
  qi.insert(root);

  while(i>minLevel) {
    NodeSet q;
    qi_1.clear();
    for(Node* node: qi) {
      if (node->hasChildren())
        for (Node* nodeChild:node->getChildren())
          q.insert(nodeChild);
      else {
        // create and insert selfchild
        Node *selfchild = new Node(node->getPoint(), node->getLevel() - 1);
        node->addChild(selfchild);
        if (selfchild->getLevel() < minLevel)
          minLevel = selfchild->getLevel();
        q.insert(selfchild);
      }
    }

    distNodePQ = getDistNodeSet(point, q);
    int j=0;
    while(j<k && !distNodePQ.empty()) {
      qi_1.insert(distNodePQ.top().second);
      if (j == k-1 || distNodePQ.size() == 1)
        threshold = distNodePQ.top().first + pow(base, i);
      distNodePQ.pop();
      j++;
    }
    while(!distNodePQ.empty() && distNodePQ.top().first <= threshold) {
      qi_1.insert(distNodePQ.top().second);
      distNodePQ.pop();
    }

    qi = qi_1;
    i--;
  }

  distNodePQ = getDistNodeSet(point, qi_1);
  std::vector<std::pair<double, Point>> knn;
  for(int j=0; j<k; j++) {
    knn.push_back(std::make_pair(distNodePQ.top().first, distNodePQ.top().second->getPoint()));
    distNodePQ.pop();
  }
  return knn;
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