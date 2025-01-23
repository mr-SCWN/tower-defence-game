#include "light.h"


light::light()
{
    light::lightPos = new float[4];
    light::lightPos[0] = 16.0f;
    light::lightPos[1] = 10.0f;
    light::lightPos[2] = 22.0f;
    light::lightPos[3] = 1.0f;

    light::ambient = new float[4];
    light::ambient[0] = 0.0f;
    light::ambient[1] = 0.0f;
    light::ambient[2] = 0.55f;
    light::ambient[3] = 1.0f;

    light::diffuse = new float[4];
    light::diffuse[0] = 1.0f;
    light::diffuse[1] = 1.0f;
    light::diffuse[2] = 1.0f;
    light::diffuse[3] = 1.0f;

    light::specular = new float[4];
    light::specular[0] = 1.0f;
    light::specular[1] = 1.0f;
    light::specular[2] = 1.0f;
    light::specular[3] = 1.0f;
}

light::~light()
{
    delete light::lightPos;
    delete light::ambient;
    delete light::diffuse;
    delete light::lightPos;
}

void light::Enable()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLightfv(GL_LIGHT0, GL_POSITION, light::lightPos);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light::ambient);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light::diffuse);

    glLightfv(GL_LIGHT0, GL_SPECULAR, light::specular);
}

void light::Disable()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_MULTISAMPLE);
}
