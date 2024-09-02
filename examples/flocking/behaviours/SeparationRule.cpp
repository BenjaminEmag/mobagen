#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  Vector2f negativeVector = Vector2f(-1.0f, -1.0f);

  float desiredDistance = desiredMinimalDistance;

  if (neighborhood.empty()) return Vector2f::zero();

  Vector2f centerMass;
  for (const Boid* b : neighborhood) 
  {
    if ((b->getPosition() - boid->getPosition()).getMagnitude() >= desiredDistance) continue;
    centerMass += b->getPosition();
  }
  centerMass = centerMass / neighborhood.size();
  separatingForce = centerMass - boid->getPosition();

  if (separatingForce.getMagnitude() >= desiredDistance) return Vector2f::zero();

  separatingForce = separatingForce.normalized() * -1;

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
