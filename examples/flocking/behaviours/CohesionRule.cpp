#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) 
{
  Vector2f cohesionForce;

  if (neighborhood.empty()) return Vector2f::zero();

  Vector2f centerMass;
  for (const Boid* boid : neighborhood)
  {
    centerMass += boid->getPosition();
  }
  centerMass = centerMass / neighborhood.size();

  // return zero if center mass is directly atop boid 
  if (boid->getPosition() - centerMass == Vector2f::zero()) return Vector2f::zero();

  cohesionForce = centerMass - boid->getPosition();
  cohesionForce = cohesionForce.normalized() ;
  return cohesionForce;
}