#include "Cursor.h"
#include "shaderprogram.h"
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>
#include <vector>
#include "Cursor_DATA.h"

Cursor::Cursor(){
	
	vector <float> a = vert_cursor();

     vector <float> b = norm_cursor();

     vector <float> c = tex_cursor();

    for (int q = 0; q < a.size(); q++) {
         this->vertices.push_back(a[q]);
   }
    for (int q = 0; q < b.size(); q++) {
        this->normals.push_back(b[q]);
   }
     for (int q = 0; q < c.size(); q++) {
         this->textureCoords.push_back(c[q]);
     }

	//generateTextureCoords();
	
}
