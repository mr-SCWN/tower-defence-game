#include "default_tower.h"
#include "shaderprogram.h"
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <vector>
#include "default_tower_DATA.h"

using namespace std;

default_tower::default_tower() {

    vector <float> a = vert();

    vector <float> b = norm();

    for (int q = 0; q < a.size(); q++) {
        this->vertices.push_back(a[q]);
    }
    for (int q = 0; q < b.size(); q++) {
        this->normals.push_back(b[q]);
    }
    generateTextureCoords();

}
