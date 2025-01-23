#include "FlyingEnemy.h"
#include "FlyingEnemy_DATA.h"
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "shaderprogram.h"
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>

using namespace std;

FlyingEnemy::FlyingEnemy(){
  vector <float> a = vert_flying_enemy();
	vector <float> b = norm_flying_enemy();
	
  vertices.clear();
  normals.clear();
  textureCoords.clear();
 for (int q = 0; q < a.size(); q++) {
         this->vertices.push_back(a[q]);
   }
    for (int q = 0; q < b.size(); q++) {
        this->normals.push_back(b[q]);
   }	
	
   generateTextureCoords();
}

void FlyingEnemy::move(double interval){
    glm::vec3 speed = glm::normalize(glm::vec3(target_position.x - position.x,0,target_position.z - position.z));

    position.x += speed.x * interval;
    position.z += speed.z * interval;
    position.y = 1.0f;
}
