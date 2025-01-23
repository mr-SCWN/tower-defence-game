#include "Functions.h"
#include <math.h>

float Functions::getHeight(float x, float z, float terrain_size){
  return (sin(x*0.3/terrain_size) + cos(z*0.4/terrain_size))/2.8;
}