#include <algorithm>
#include <list>
#include <map>
#include <utility>
#include <cmath>

#include "node.h"

/**
 * Helper function that will help estimate the remaining distance (the better
 * the heuristics, the faster A* will be)
 * Here we're just calculating the Ecludian distance between *current* and
 * *goal* because each node's key is just a 2D vector
 * @param  {Node*} current
 * @param  {Node*} goal
 * @return {float} an estimation of the remaining distance between current and goal
 */
float heuristicCostEstimate(Node* current, Node* goal){
  float x = goal->key[0] - current->key[0];
  float y = goal->key[1] - current->key[1];
  return sqrt(x*x + y*y);
}


/**
 * Helper method that builds a path
 * @param  {map<Node*, Node*>} came_from => a hash map that represents the path
 * @param  {Node*} current_node => the first node of the path
 * @return {list<Node*>}
 */
std::list<Node*> reconstructurePath(std::map<Node*, Node*> came_from, Node* current_node) {
  std::list<Node*> path (1, current_node);

  if(came_from[current_node] == NULL) {
    return path;
  }
  path = reconstructurePath(came_from, came_from[current_node]);
  path.push_back(current_node);
  return path;
}

/**
 * A* algorithm.
 *
 * This function takes a start and a goal {Node*} and, assuming
 * that you can reach the goal node from the start node, computes the almost
 * shortest path from the start to the goal. It uses a heuristic function to
 * compute some estimated remaining distance that can make this algorithm
 * very efficient and fast if it's precise.
 * @param  {Node*} start
 * @param  {Node*} goal
 * @return {list<Node*>} a list of nodes that compose a path from start to goal
 */
std::list<Node*> astart(Node* start_node, Node* goal_node) {
  // This list is used to represent the set of visited nodes
  std::list<Node*> closed_set;

  // List used to represent the set of nodes that should be visited
  std::list<Node*> open_set (1, start_node);

  // Hash map used to represent a path
  // This is one of the keys of this algorithm. If you have a path like
  // a->b->c then it will be represented like so
  // came_from[a] = b; came_from[b] = c; came_from[c] = NULL;
  std::map<Node*, Node*> came_from;

  // Temporary variable used to keep track of the current {Node*}
  Node* current = start_node;

  // Temporary variabe used to calculate the next g_score and check how
  // different it is compared to the previous g_score of the *neighbour* of
  // *current*
  float tentative_g_score = 0;

  // Set the start's node g_score to 0 because it's the start node
  start_node->g_score = 0;
  start_node->f_score = 0 + heuristicCostEstimate(start_node, goal_node);

  // Loop until the set of possible nodes is empty
  while(!open_set.empty()) {
    // set the current to be the first element in *open_set*
    current = open_set.front();

    // Find the {Node*} that has the smallest f_score in *open_set*
    for (std::list<Node*>::iterator it = open_set.begin(); it != open_set.end(); ++it) {
      if(current->f_score > (*it)->f_score) {
        current = *it;
      }
    }

    // If the current {Node*} is the goal_node then you're done
    if(current == goal_node) {
      return reconstructurePath(came_from, goal_node);
    }

    // We now add *current* to the path
    open_set.remove(current);
    closed_set.push_back(current);

    // Look through the neighbours of *current* and check if we can update
    // their g_score (aka get to those {Node*} faster than the previous way we
    // got there)
    for (std::list<std::pair <Node*, float> >::iterator edge = current->neighbours.begin(); edge != current->neighbours.end(); ++edge) {

      // The edge is pair of a Node* and an float (the cost of going there)
      // To simplify we assign the first part of the pair to *neighbour*
      Node *neighbour = edge->first;

      // Check if *neighbour* is already in the set closed_set
      // If yes, we skip it
      std::list<Node*>::iterator isIn = find(closed_set.begin(), closed_set.end(), neighbour);
      if(isIn != closed_set.end()) {
        continue;
      }

      // Calculate the *neighbour* 's g_score
      tentative_g_score = current->g_score + edge->second;

      // Check if *neighbour* is already in open_set, if yes then it might
      // be faster to go from *current* to *neighbour* than the previous way
      // of getting to *neigbour*
      isIn = find(open_set.begin(), open_set.end(), neighbour);

      // If *neighbour* is in open_set or if its g_score is bigger than the one we calculated comin from *current* node
      if(isIn == open_set.end() || tentative_g_score < neighbour->g_score) {

        // Update the hashmap from *neighbour* to *current* which will later be
        // used to build the path
        came_from[neighbour] = current;

        // Update the g_score and the f_score of *neighbour* because going from
        // *current* to *neighbour* is cheaper than the previous way of going
        // to *neighbour*
        neighbour->g_score = tentative_g_score;
        neighbour->f_score = tentative_g_score + heuristicCostEstimate(neighbour, goal_node);

        // We add *neighbour* to the open_set if it's not already in there
        if(isIn == open_set.end()) {
          open_set.push_back(neighbour);
        }
      }
    }
  }

  // If we came out of the loop without calling the reconstructPath method
  // then we couldn't reach *goal_node* so we return *open_set* which is an
  // empty list
  return open_set;
}
