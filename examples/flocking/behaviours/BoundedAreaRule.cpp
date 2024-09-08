#include "BoundedAreaRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"
#include <iostream>

Vector2f BoundedAreaRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f wallForce = Vector2f::zero();

  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;
  float threshold = dist;

  Vector2f pos = boid->getPosition() + boid->getVelocity();

  // Use SDL to return no force if boid is inside Boundry
  SDL_Point point{static_cast<int>(pos.x), static_cast<int>(pos.y)};
  SDL_Rect rect{static_cast<int>(dist), static_cast<int>(dist), static_cast<int>(size.x - 2 * dist), static_cast<int>(size.y - 2 * dist)};
  if (SDL_PointInRect(&point, &rect)) return Vector2f::zero();

  // set boundry values based off threshold and size of box
  float leftBoundary = dist + threshold;
  float rightBoundary = size.x - dist - threshold;
  float topBoundary = dist + threshold;
  float bottomBoundary = size.y - dist - threshold;

  // divide by threshold to make the force proportional to how far away you are from the wall 
  // Love ternary operator
  wallForce.x = (pos.x < leftBoundary) ? (leftBoundary - pos.x) / threshold :
                (pos.x > rightBoundary) ? (rightBoundary - pos.x) / threshold : 0;

  wallForce.y = (pos.y < topBoundary) ? (topBoundary - pos.y) / threshold :
                (pos.y > bottomBoundary) ? (bottomBoundary - pos.y) / threshold : 0;

  return wallForce;
}

bool BoundedAreaRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  auto size = this->world->engine->window->size();
  auto widthWindows = size.x;
  auto heightWindows = size.y;
  bool valueHasChanged = false;

  // We cap the max separation as the third of the min of the width.height
  auto minHeightWidth = std::min(widthWindows, heightWindows);

  if (ImGui::SliderInt("Desired Distance From Borders", &desiredDistance, 0.0f, (int)(minHeightWidth / 3), "%i")) {
    valueHasChanged = true;
  }

  return valueHasChanged;
}

void BoundedAreaRule::draw(const Boid& boid, SDL_Renderer* renderer) const {
  FlockingRule::draw(boid, renderer);
  auto size = this->world->engine->window->size();
  auto dist = (float)desiredDistance;

  // Draw a rectangle on the map
  Polygon::DrawLine(renderer, Vector2f(dist, dist), Vector2f(size.x - dist, dist), Color::Red);                    // TOP
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, dist), Vector2f(size.x - dist, size.y - dist), Color::Red);  // RIGHT
  Polygon::DrawLine(renderer, Vector2f(size.x - dist, size.y - dist), Vector2f(dist, size.y - dist), Color::Red);  // Bottom
  Polygon::DrawLine(renderer, Vector2f(dist, size.y - dist), Vector2f(dist, dist), Color::Red);                    // LEFT
}