#include <list>
#include <utility>

#ifndef __NODE_H__
#define __NODE_H__ value

class Node
{
  public:
    Node(float* a) {
      this->key = a;
      this->g_score = 2147483647;
      this->f_score = 0;
    }

    ~Node(){}

    void addNeighbour(Node* n, float cost) {
      this->neighbours.push_back(std::pair<Node*, float>(n, cost));
    }

    /* data */
    float* key;
    float g_score;
    float f_score;
    std::list<std::pair <Node*, float> > neighbours;
};

#endif
