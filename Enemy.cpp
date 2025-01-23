#include "Enemy.h"
#include "shaderprogram.h"
#include "Functions.h"
#include <cstdlib>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <vector>
#include "enemy_DATA.h"

using namespace std;

Enemy::Enemy() {

     vector <float> a = vert_enemy();

     vector <float> b = norm_enemy();

    // vector <float> c = texi();

    for (int q = 0; q < a.size(); q++) {
         this->vertices.push_back(a[q]);
   }
    for (int q = 0; q < b.size(); q++) {
        this->normals.push_back(b[q]);
   }
    // for (int q = 0; q < c.size(); q++) {
    //     this->textureCoords.push_back(c[q]);
    // }


  generateTextureCoords();

}

glm::vec3 Enemy::getPosition(){
    return position;
}

void Enemy::setPosition(glm::vec3 position){
    this->position = position;
}
void Enemy::setSpeed(glm::vec3 speed){
    this->speed = speed;
}
void Enemy::setTargetPosition(glm::vec3 position){
    this->target_position = position;
}

float Enemy::getRotation(){
  glm::vec3 direction = glm::normalize(glm::vec3(target_position.x - position.x,0,target_position.z - position.z));
  glm::vec3 oldDirection = glm::vec3(0,0,1.0f);
  float angle = atan2(direction.x, direction.z) - atan2(oldDirection.x, oldDirection.z);
  return angle;
}

float Enemy::getRotationX(){
    glm::vec3 direction = glm::normalize(glm::vec3(target_position.x - position.x,0,target_position.z - position.z));
    glm::vec3 pointBefore = position+glm::vec3(direction.x/20,0,direction.z/20);
    pointBefore.y = Functions::getHeight(pointBefore.x, pointBefore.z, 0.2f);
    glm::vec3 newDirection = glm::normalize(pointBefore-position);

    float angle = atan2(newDirection.y, newDirection.z) - atan2(direction.y, direction.z);

    if(newDirection.z<0)
        return angle;
    return -angle;
}

void Enemy::move(double interval){
  
  glm::vec3 speed = glm::normalize(target_position - position);

  position.x += speed.x * interval;
  position.z += speed.z * interval;
  position.y = Functions::getHeight(position.x, position.z, 0.2f);
}

void Enemy::die(){
    
    /*
      tutaj jakaś animacja
    */
    spawn();
}

void Enemy::spawn(float how_far){
    glm::vec3 randomDirection = glm::normalize(glm::vec3(sin((float)rand()),0,sin((float)rand())));
        
    randomDirection.x *= how_far;
    randomDirection.z *= how_far;
    position = target_position + randomDirection;
    if(abs(position.z - target_position.z)<5.0f)
        position.z = target_position.z + 5.0f;
}

void Enemy::attack(){
    /*
        jakaś animacja, nie wiem czy coś więcej
    */
    spawn();
}
