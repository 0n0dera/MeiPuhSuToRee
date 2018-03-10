#include "player.h"
#include "fixed_camera.h"

Player::Player(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll)
		: Entity(position, speed, yaw, pitch, roll)
		, _camera(nullptr) {}

Player::~Player() {}

void Player::Move(EntityMovement direction, GLfloat delta) {
	_yaw = _camera->Yaw();
	switch (direction)
	{
	case FORWARD:
		break;
	case BACKWARD:
		_yaw += glm::pi<GLfloat>();
		break;
	case RIGHT:
		_yaw -= glm::half_pi<GLfloat>();
		break;
	case LEFT:
		_yaw += glm::half_pi<GLfloat>();
		break;
	}
	// need to update camera distance when player moves
	// camera needs to jump behind player
	_camera->ResetDistance(_nextYaw, _yaw);
	Entity::Move(direction, delta);
}

void Player::SetCamera(FixedCamera * camera) {
	_camera = camera;
}
