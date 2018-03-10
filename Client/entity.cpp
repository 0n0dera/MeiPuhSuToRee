#include "constants.h"
#include "entity.h"

Entity::Entity(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll)
		: _position(position)
		, _front()
		, _right()
		, _up()
		, _speed(speed)
		, _yaw(yaw)
		, _pitch(pitch)
		, _roll(roll)
		, _nextYaw(yaw)
		, _nextPitch(pitch)
		, _nextRoll(roll) {
	CalculateDirectionVectors();
}

Entity::~Entity() {}

void Entity::Move(EntityMovement direction, GLfloat delta) {
	CalculateDirectionVectors();
	GLfloat velocity = delta * _speed;
	_position += _front * velocity;
}

void Entity::Rotate(GLfloat yaw, GLfloat pitch, GLfloat roll) {
	_nextYaw += yaw;
	_nextPitch += pitch;
	_nextRoll += roll;
}

void Entity::CalculateDirectionVectors() {
	_yaw = _nextYaw;
	_pitch = _nextPitch;
	_roll = _nextRoll;
	_front.x = -cos(_yaw);
	_front.y = sin(_pitch);
	_front.z = sin(_yaw) * cos(_pitch);
	_front = glm::normalize(_front);
	_right = glm::normalize(glm::cross(_front, constants::WORLD_UP));
	_up = glm::normalize(glm::cross(_right, _front));
}