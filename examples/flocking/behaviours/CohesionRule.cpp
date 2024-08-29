#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {

  Vector2f zeroVector(0.0f, 0.0f);

  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  
  // find center of mass
  Vector2f centerMass;
  for (const Boid* boid : neighborhood)
  {
    centerMass += boid->getPosition();
  }
  centerMass = centerMass / neighborhood.size();

  if (boid->getPosition() - centerMass == zeroVector) return zeroVector;

  cohesionForce = centerMass - boid->getPosition();
  cohesionForce = cohesionForce.normalized();
  return cohesionForce;
}