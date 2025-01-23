#include "Boom.h"
#include "shaderprogram.h"
#include "Functions.h"
#include <cstdlib>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <vector>
#include "Boom_DATA.h"

using namespace std;

Boom::Boom(){
    vector <float> a = vert_boom();

     vector <float> b = norm_boom();

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
