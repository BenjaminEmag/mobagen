#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path = generatePath(world);

  if (path.empty()) {
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();

    std::vector<Point2D> neighbors = world->getVisitableNeighbors(pos);
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, neighbors.size() - 1);

    int randomIndex = distr(eng);
    return neighbors[randomIndex];
  }


Point2D currentPosition = world->getCat();
Point2D nextMove = path.front();

return nextMove;
}
