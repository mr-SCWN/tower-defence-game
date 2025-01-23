#include "Terrain.h"
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>

float Terrain::height(int i, int j){
  return (sin(j*0.3) + cos(i*0.4))/2.8;
}

void Terrain::generateTerrain(int terrain_size, float cell_size){


  for(int i=0;i<terrain_size;i++)
    for(int j=0;j<terrain_size;j++){
      vertices.push_back(j*cell_size);
      vertices.push_back(height(i,j));
      vertices.push_back(i*cell_size);
      vertices.push_back(1.0f);

      vertices.push_back((j+1)*cell_size);
      vertices.push_back(height(i,j+1));
      vertices.push_back(i*cell_size);
      vertices.push_back(1.0f);

      vertices.push_back(j*cell_size);
      vertices.push_back(height(i+1,j));
      vertices.push_back((i+1)*cell_size);
      vertices.push_back(1.0f);

      vertices.push_back((j+1)*cell_size);
      vertices.push_back(height(i+1,j+1));
      vertices.push_back((i+1)*cell_size);
      vertices.push_back(1.0f);

      vertices.push_back(j*cell_size);
      vertices.push_back(height(i+1,j));
      vertices.push_back((i+1)*cell_size);
      vertices.push_back(1.0f);

      vertices.push_back((j+1)*cell_size);
      vertices.push_back(height(i,j+1));
      vertices.push_back(i*cell_size);
      vertices.push_back(1.0f);
    }
}

Terrain::Terrain(){
  generateTerrain(140,0.2f);
  generateNormals();
  generateTextureCoords();
}