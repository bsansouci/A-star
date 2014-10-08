#include <iostream>
#include "astar.cpp"

int main() {
  // We're creating 4 {Node} such that
  //  /--4-> 2 --1-\
  // 1              |-> 4
  //  \--5-> 3 --1-/
  //  So here the shortest path would be 1 -> 2 -> 4

  float pos1[2] = {1.0f, 1.0f};
  Node n1 = Node(pos1);
  float pos2[2] = {2.0f, 2.0f};
  Node n2 = Node(pos2);
  float pos3[2] = {2.0f, 0.0f};
  Node n3 = Node(pos3);
  float pos4[2] = {4.0f, 1.0f};
  Node n4 = Node(pos4);

  n1.addNeighbour(&n2, 4.0f);
  n1.addNeighbour(&n3, 5.0f);
  n2.addNeighbour(&n4, 1.0f);
  n3.addNeighbour(&n4, 1.0f);

  std::list<Node*> l = astart(&n1, &n4);
  for (std::list<Node*>::iterator i = l.begin(); i != l.end(); ++i) {
    std::cout << (*i)->key[0] << " " << (*i)->key[1] << std::endl;
  }
  return 0;
}
