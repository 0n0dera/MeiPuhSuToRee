#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "constants.h"

class Player;

class FixedCamera
{
public:
	FixedCamera(Player& player);
	glm::mat4 GetViewMatrix();
	void Rotate(double dx, double dy);
	void ChangeZoom(GLfloat zoom);
	void ResetDistance(GLfloat newYaw, GLfloat oldYaw);

	// getters
	GLfloat Zoom() const;
	GLfloat Yaw() const;
private:
	GLfloat GetMaxY() const;

	Player& _player;
	glm::vec3 _distance;
	glm::vec3 _position;
	GLfloat _zoom;
	GLfloat _maxY;
	GLfloat _yaw;
};

inline GLfloat FixedCamera::Zoom() const {
	return _zoom;
}

inline GLfloat FixedCamera::Yaw() const {
	return _yaw;
}

inline GLfloat FixedCamera::GetMaxY() const {
	return glm::length(_distance) - glm::length(_distance) / 5;
}