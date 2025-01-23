#include "Tower.h"
#include <glm/trigonometric.hpp>

glm::vec3 Tower::getPosition(){
    return position;
}
void Tower::setPosition(glm::vec3 position){
  this->position = position;
}

float Tower::getRange(){
  return range;
}

void Tower::setBasePosition(glm::vec3 position){
  this->base_position = position;
}

float Tower::getRotation(){
  glm::vec3 direction = glm::normalize(glm::vec3(base_position.x - position.x,0,base_position.z - position.z));
  glm::vec3 oldDirection = glm::vec3(0,0,1.0f);
  float angle = atan2(direction.x, direction.z) - atan2(oldDirection.x, oldDirection.z);
  return angle + glm::radians(180.0f);
}


void Tower::shoot(){
  /*
    jakaś animacja
  */
}