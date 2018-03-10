#pragma once
#include "entity.h"

class FixedCamera;

class Player : public Entity
{
public:
	Player(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw = 0.0,
		GLfloat pitch = 0.0,
		GLfloat roll = 0.0
	);
	virtual ~Player() override;

	void Move(EntityMovement direction, GLfloat delta) override;
	void SetCamera(FixedCamera* camera);
private:
	FixedCamera* _camera;
};