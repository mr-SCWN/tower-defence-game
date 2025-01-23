#include "Base.h"
#include "shaderprogram.h"
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <vector>
#include "Base_DATA.h"

using namespace std;

Base::Base() {

    vector <float> a = vert_base();

    vector <float> b = norm_base();

    for (int q = 0; q < a.size(); q++) {
        this->vertices.push_back(a[q]);
    }
    for (int q = 0; q < b.size(); q++) {
        this->normals.push_back(b[q]);
    }
    generateTextureCoords();

}
