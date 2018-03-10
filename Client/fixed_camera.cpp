#include "fixed_camera.h"
#include "player.h"
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>
#include <iostream>

FixedCamera::FixedCamera(Player& player)
	: _player(player)
	, _distance({ 0.0f, 0.0f, constants::CAMERA_DISTANCE })
	, _position(_player.Position() + _distance)
	, _zoom(constants::CAMERA_ZOOM)
	, _maxY(GetMaxY())
	, _yaw(0) {}

glm::mat4 FixedCamera::GetViewMatrix() {
	glm::vec3 position = _player.Position() + _distance;
	return glm::lookAt(position, _player.Position(), constants::WORLD_UP);
}

void FixedCamera::Rotate(double dx, double dy) {
	GLfloat dYaw = dx * constants::MOUSE_SENS;
	GLfloat dPitch = dy * constants::MOUSE_SENS;
	glm::vec3 v1 = _distance;
	std::cout << dy << std::endl << _maxY << std::endl;;
	if ((_distance.y <= _maxY && _distance.y >= 0)
		|| (_distance.y > _maxY && dy > 0)
		|| (_distance.y < 0 && dy < 0)) {
		v1 = glm::rotate(v1, dPitch, glm::cross(-_distance, constants::WORLD_UP));
	}
	v1 = glm::rotate(v1, dYaw, constants::WORLD_UP);
	_distance.x = v1.x;
	_distance.y = v1.y;
	_distance.z = v1.z;
	_player.Rotate(dYaw, 0, 0);
	printf("%f %f %f\n", _distance.x, _distance.y, _distance.z);
}

// zoom is either -1 or 1
void FixedCamera::ChangeZoom(GLfloat zoom) {
	_distance += zoom * _distance * constants::ZOOM_FACTOR;
	_maxY = GetMaxY();
}

void FixedCamera::ResetDistance(GLfloat newYaw, GLfloat oldYaw) {
	GLfloat dYaw = oldYaw - newYaw;
	_distance = glm::rotate(_distance, dYaw, constants::WORLD_UP);
}