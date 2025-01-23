#include "Player.h"
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include "Functions.h"

Player::Player(){
  pos = glm::vec3(0.0f,0.0f,0.0f);
  cursor = glm::vec3(7.0f,1.0f,0.0f);
  speed = glm::vec3(0.0f,0.0f,0.0f);
  cash = 3;
  hp = 3;
}

void Player::update_position(double interval,glm::vec3 basePosition){
  glm::vec3 newPos = pos;
  newPos.x += speed.x * interval;
  newPos.z += speed.z * interval;
  if(glm::length(newPos-basePosition) < 5.0f){
    pos = newPos;
    cursor.x += speed.x * interval;
    cursor.z += speed.z * interval;
  }
  cursor.y = Functions::getHeight(cursor.x, cursor.z, 0.2f);
}