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

	// getters
	GLfloat Zoom() const;
private:
	GLfloat GetMaxY() const;

	Player& _player;
	glm::vec3 _distance;
	GLfloat _zoom;
    GLfloat _upRotateAngle = 0.0f;
    const GLfloat kMaxUpRotate = 0.5f;
};

inline GLfloat FixedCamera::Zoom() const {
	return _zoom;
}

inline GLfloat FixedCamera::GetMaxY() const {
	return glm::length(_distance) - glm::length(_distance) / 5;
}
