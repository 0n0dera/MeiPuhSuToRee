#pragma once
#include "entity.h"

class Player : public Entity
{
public:
	Player(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw = constants::FORWARD_YAW,
		GLfloat pitch = 0.0,
		GLfloat roll = 0.0
	);
	virtual ~Player() override;

	void Move(EntityMovement direction, GLfloat delta) override;
private:
};