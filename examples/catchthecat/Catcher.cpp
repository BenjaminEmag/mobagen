#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  Point2D catPosition = world->getCat();
  std::vector<Point2D> path = generatePath(world);

  // 6 is a magic number gotten from testing
  if (path.size() > (world->getWorldSideSize() / 5)) {
    int blockIndex = world->getWorldSideSize() / 5;

    Point2D blockPosition = path[blockIndex];

    if (blockPosition != catPosition) {
      return blockPosition;
    }
  }

  if (!path.empty()) {
    Point2D lastPosition = path.back();

    if (!world->getContent(lastPosition) && lastPosition != catPosition) {
      return lastPosition;
    }
  }

  std::vector<Point2D> potentialBlocks = {World::NE(catPosition), World::NW(catPosition), World::E(catPosition),
                                          World::W(catPosition),  World::SE(catPosition), World::SW(catPosition)};

  for (const Point2D& position : potentialBlocks) {
    if (!world->getContent(position) && position != catPosition) {
      return position;
    }
  }
}
