#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"

class Entity
{
public:
	enum EntityMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	Entity(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll
	);
	// probs need to make this virtual in the future
	virtual ~Entity();

	virtual void Move(EntityMovement direction, GLfloat delta);
	virtual void Rotate(GLfloat yaw, GLfloat pitch, GLfloat roll);

	// getters
	glm::vec3 Position() const;
	glm::vec3 Front() const;
	glm::vec3 Right() const;
	glm::vec3 Up() const;
	GLfloat Speed() const;
	GLfloat Yaw() const;
	GLfloat Pitch() const;
	GLfloat Roll() const;
protected:
	// rotation around Y axis
	GLfloat _yaw;
	// rotation around X axis
	GLfloat _pitch;
	// rotation around Z axis
	GLfloat _roll;

	// These are updated in Rotate() when camera moves.
	// When player finally moves, direction vectors get calculated
	// based on these values.
	// Could replace this by getting a pointer to camera and using
	// camera's distance vector but I'd rather do this
	GLfloat _nextYaw;
	GLfloat _nextPitch;
	GLfloat _nextRoll;
	// unit vector in direction entity is facing
	glm::vec3 _front;
private:
	// entity's position in the world
	glm::vec3 _position;
	// unit vector to the right of entity
	glm::vec3 _right;
	// unit vector up from entity
	glm::vec3 _up;
	// movement speed
	GLfloat _speed;

	void CalculateDirectionVectors();
};

inline glm::vec3 Entity::Position() const {
	return _position;
}
inline glm::vec3 Entity::Front() const {
	return _front;
}
inline glm::vec3 Entity::Right() const {
	return _right;
}
inline glm::vec3 Entity::Up() const {
	return _up;
}
inline GLfloat Entity::Speed() const {
	return _speed;
}
inline GLfloat Entity::Yaw() const {
	return _yaw;
}
inline GLfloat Entity::Pitch() const {
	return _pitch;
}
inline GLfloat Entity::Roll() const {
	return _roll;
}