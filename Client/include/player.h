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
	virtual void Collide(Entity* entity) override;
    virtual void Recoil(const glm::vec3& recoilVec) override;
    virtual void Jump(float yVel = 5.0f) override;
private:
};
