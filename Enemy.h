#pragma once
#include "Drawable.h"
#include <glm/fwd.hpp>


using namespace std;

class Enemy : public Drawable {
protected:
	glm::vec3 position;
	glm::vec3 speed;
	glm::vec3 target_position;

public:
	Enemy();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getRotation();
	float getRotationX();
	void setTargetPosition(glm::vec3 position);
	void setSpeed(glm::vec3 speed);
	void move(double interval);
	void die();
	void spawn(float how_far = 10.0f);
	void attack();
};
