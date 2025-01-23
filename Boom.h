#pragma once
#include "Drawable.h"
#include <glm/fwd.hpp>


using namespace std;

class Boom : public Drawable {
protected:
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 target_position;

public:
	Boom();

};