#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include "shaderprogram.h"

class Drawable{

  protected:
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> textureCoords;
    GLuint texture;

  public:
    Drawable(std::vector<float> vertices,std::vector<float> normals,std::vector<float> textureCoords, GLuint texture);
    Drawable(GLuint texture);
    Drawable();
    void generateNormals();
    void generateTextureCoords();
    void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M);
    void setTexture(GLuint texture);
};