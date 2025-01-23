#pragma once
#include <GL/glew.h>

class light{
    protected:
        float* lightPos;
        float* ambient;
        float* diffuse;
        float* specular;
    public:
        light();
        ~light();
        void Enable();
        void Disable();
};