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
		GLfloat roll,
		GLfloat boundingBoxDeltaX,
		GLfloat boundingBoxDeltaY,
		GLfloat boundingBoxDeltaZ
	);
	// probs need to make this virtual in the future
	virtual ~Entity();

	virtual void Tick(GLfloat deltaTime, GLfloat groundLevel);
	virtual void Move(EntityMovement direction, GLfloat delta);
	virtual void Rotate(GLfloat yaw, GLfloat pitch, GLfloat roll);
	virtual void Jump();

	// rotation around Y axis
	GLfloat yaw;
	// rotation around X axis
	GLfloat pitch;
	// rotation around Z axis
	GLfloat roll;

	// These are updated in Rotate() when camera moves.
	// When player finally moves, direction vectors get calculated
	// based on these values.
	GLfloat nextYaw;
	GLfloat nextPitch;
	GLfloat nextRoll;
	// unit vector in direction entity is facing
	glm::vec3 front;
	// entity's position in the world
	glm::vec3 position;
	// unit vector to the right of entity
	glm::vec3 right;
	// unit vector up from entity
	glm::vec3 up;
	// movement speed
	GLfloat speed;
	// y velocity
	GLfloat yVelocity = 0.0f;
	// on ground
	bool grounded = true;
	
	// delta x/y/z for bounding box. half of actual x, y, z lengths
	GLfloat boundingBoxDeltaX;
	GLfloat boundingBoxDeltaY;
	GLfloat boundingBoxDeltaZ;

private:
	void CalculateDirectionVectors();
};