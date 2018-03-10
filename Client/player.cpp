#include "player.h"
#include "fixed_camera.h"
#include <iostream>

Player::Player(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll)
		: Entity(position, speed, yaw, pitch, roll) {}

Player::~Player() {}

void Player::Move(EntityMovement direction, GLfloat delta) {
	static EntityMovement last = FORWARD;
	if (direction != last) {
		switch (last) {
		case FORWARD:
			switch (direction) {
			case BACKWARD:
				_nextYaw += glm::pi<GLfloat>();
				break;
			case RIGHT:
				_nextYaw -= glm::half_pi<GLfloat>();
				break;
			case LEFT:
				_nextYaw += glm::half_pi<GLfloat>();
				break;
			}
			break;
		case BACKWARD:
			switch (direction) {
			case FORWARD:
				_nextYaw += glm::pi<GLfloat>();
				break;
			case RIGHT:
				_nextYaw += glm::half_pi<GLfloat>();
				break;
			case LEFT:
				_nextYaw -= glm::half_pi<GLfloat>();
				break;
			}
			break;
		case RIGHT:
			switch (direction) {
			case BACKWARD:
				_nextYaw -= glm::half_pi<GLfloat>();
				break;
			case FORWARD:
				_nextYaw += glm::half_pi<GLfloat>();
				break;
			case LEFT:
				_nextYaw += glm::pi<GLfloat>();
				break;
			}
			break;
		case LEFT:
			switch (direction) {
			case RIGHT:
				_nextYaw -= glm::pi<GLfloat>();
				break;
			case BACKWARD:
				_nextYaw += glm::half_pi<GLfloat>();
				break;
			case FORWARD:
				_nextYaw -= glm::half_pi<GLfloat>();
				break;
			}
			break;
		}
	}
	last = direction;
	// need to update camera distance when player moves
	// camera needs to jump behind player
	Entity::Move(direction, delta);
	printf("%f, %f, %f\n", _front.x, _front.y, _front.z);
}