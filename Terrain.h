#pragma once
#include "Drawable.h"

class Terrain : public Drawable{
  
  public:
    float height(int i, int j);
    void generateTerrain(int terrain_size, float cell_size);
    Terrain();

};