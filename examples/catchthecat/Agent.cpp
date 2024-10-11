#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

struct Node {
  Point2D point;
  int accDist;
  int heuristicDist;

  Node(Point2D pos, float c, float p) : point(pos), accDist(c), heuristicDist(p) {}

  // Comparison operator for the priority queue
  bool operator<(const Node& rhs) const { return accDist + heuristicDist > rhs.accDist + rhs.heuristicDist; }
};

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  std::priority_queue<Node> frontier;        // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  // Initialize the start node
  frontier.emplace(catPos, 0, heuristic(catPos, w->getWorldSideSize()));  // 0 is the accumulated distance
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    Node currNode = frontier.top();
    frontier.pop();

    visited[currNode.point] = true;

    if (w->isBorder(currNode.point)) {
      borderExit = currNode.point;  // Found an exit
      break;                        
    }

    std::vector<Point2D> neighbors = w->getVisitableNeighbors(currNode.point);

    for (Point2D& point : neighbors) {
      if (visited.find(point) == visited.end()) {
        int newAccDist = currNode.accDist + 1;
        int newHeuristicDist = heuristic(point, w->getWorldSideSize());

        if (frontierSet.find(point) == frontierSet.end() || newAccDist < currNode.accDist) {
          // Update cameFrom
          cameFrom[point] = currNode.point;

          // Push the neighbor into the frontier
          frontier.emplace(point, newAccDist, newHeuristicDist);
          frontierSet.insert(point);
        }
      }
    }
  }

  if (borderExit != Point2D::INFINITE) {
    std::vector<Point2D> path;
    for (Point2D at = borderExit; at != catPos; at = cameFrom[at]) {
      path.push_back(at);
    }
    std::reverse(path.begin(), path.end());  // Reverse to get the path from cat to exit
    return path;
  }

  return std::vector<Point2D>();  // Return empty vector indicating no path
}

float Agent::heuristic(const Point2D& p, int sideSize) {
  int sideOver2 = sideSize / 2;
  return std::min(std::abs(p.x) - sideOver2, std::abs(p.y) - sideOver2);
}