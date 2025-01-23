#include "Drawable.h"
#include "shaderprogram.h"
#include "lodepng.h"
#include <cstdio>
#include <glm/gtc/type_ptr.hpp>


void Drawable::generateNormals(){
  for(int i=0;i<vertices.size()-12;i+=12){
    glm::vec3 v1 = glm::vec3(vertices[i],vertices[i+1],vertices[i+2]);
    glm::vec3 v2 = glm::vec3(vertices[i+4],vertices[i+5],vertices[i+6]);
    glm::vec3 v3 = glm::vec3(vertices[i+8],vertices[i+9],vertices[i+10]);
    glm::vec3 edge1 = v1 - v2; 
    glm::vec3 edge2 = v3 - v2;
    glm::vec3 normal = glm::normalize(glm::cross(edge1,edge2));

    for (int j = 0; j < 3; j++) {
      normals.push_back(normal.x); 
      normals.push_back(normal.y); 
      normals.push_back(normal.z); 
      normals.push_back(0.0f);
    }
    
  }
}

void Drawable::generateTextureCoords(){
  for(int i=0;i<vertices.size();i+=4){
    textureCoords.push_back(vertices[i]);
    textureCoords.push_back(vertices[i+2]);
  }
}

void Drawable::setTexture(GLuint texture){
  this->texture = texture;
}

void Drawable::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
  spLambertTextured->use();

  glUniformMatrix4fv(spLambertTextured->u("P"), 1, false, glm::value_ptr(P)); 
  glUniformMatrix4fv(spLambertTextured->u("V"), 1, false, glm::value_ptr(V)); 
  glUniformMatrix4fv(spLambertTextured->u("M"), 1, false, glm::value_ptr(M)); 

  GLuint vertexAttributeLocation = spLambertTextured->a("vertex");
  glEnableVertexAttribArray(vertexAttributeLocation);
  glVertexAttribPointer(vertexAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, vertices.data());

  GLuint normalsAttributeLocation = spLambertTextured->a("normal");
  glEnableVertexAttribArray(normalsAttributeLocation);
  glVertexAttribPointer(normalsAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, normals.data());

  GLuint textureCoordsAttributeLocation = spLambertTextured->a("texCoord");
  glEnableVertexAttribArray(textureCoordsAttributeLocation);
  glVertexAttribPointer(textureCoordsAttributeLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoords.data());

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D,texture);
	

  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 4);

  glDisableVertexAttribArray(vertexAttributeLocation);
  glDisableVertexAttribArray(normalsAttributeLocation);
  glDisableVertexAttribArray(textureCoordsAttributeLocation);
}

Drawable::Drawable(){}
Drawable::Drawable(GLuint texture){
  this->texture = texture;
}

Drawable::Drawable(std::vector<float> vertices,std::vector<float> normals,std::vector<float> textureCoords, GLuint texture){
  this->vertices = vertices;
  this->normals = normals;
  this->textureCoords = textureCoords;
  this->texture = texture;
}
