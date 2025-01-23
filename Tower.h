#pragma once
#include "Drawable.h"
#include <glm/fwd.hpp>
class Tower : public Drawable{
  
  glm::vec3 position;
  glm::vec3 base_position;
  float range = 0.9f;
  
  public:
  glm::vec3 getPosition();
  float getRange();
  float getRotation();
  void setPosition(glm::vec3 position);
  void setBasePosition(glm::vec3 position);
  void shoot();
};