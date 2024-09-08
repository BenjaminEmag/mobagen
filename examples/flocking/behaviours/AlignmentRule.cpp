#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  if (neighborhood.empty()) return Vector2f::zero();

  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();
  Vector2f accVelocity = Vector2f::zero();

  for (const Boid* b : neighborhood) 
  {
    accVelocity += b->getVelocity();
  }

  averageVelocity = accVelocity / neighborhood.size();
  return Vector2f::normalized(averageVelocity);
}