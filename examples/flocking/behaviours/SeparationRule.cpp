#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  if (neighborhood.empty()) return Vector2f::zero();

  Vector2f centerMass;
  int i = 0;
  for (const Boid* b : neighborhood) 
  {
      // accumulate position of boids within the desired seperation distance
    if (Vector2f::DistanceSquared(b->getPosition(), boid->getPosition()) >= (desiredDistance * desiredDistance)) continue;
    centerMass += b->getPosition();
    i++;
  }

  if (i == 0) return Vector2f::zero();
  centerMass = centerMass / i;

  separatingForce = boid->getPosition() - centerMass;

  if (separatingForce.getMagnitude() >= desiredDistance) return Vector2f::zero();

  // divide by desired distance to make the force proportional to the distance
  separatingForce = separatingForce.normalized() / ((Vector2f::Distance(centerMass, boid->getPosition()) / desiredDistance));

  // arbitrary constant value that makes the seperation feel better
  return separatingForce * 0.5;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
