#include "fixed_camera.h"
#include "player.h"
#include <glm/gtx/rotate_vector.hpp>
#include <algorithm>
#include <iostream>
using namespace std;

FixedCamera::FixedCamera(Player& player)
	: _player(player)
	, _distance({ 0.0f, 0.0f, constants::CAMERA_DISTANCE })
	, _zoom(constants::CAMERA_ZOOM) {}

glm::mat4 FixedCamera::GetViewMatrix() {
	glm::vec3 position = _player.position + _distance;
	return glm::lookAt(position, _player.position, constants::WORLD_UP);
}

void FixedCamera::Rotate(double dx, double dy) {
	GLfloat dYaw = -dx * constants::MOUSE_SENS;
	GLfloat dPitch = dy * constants::MOUSE_SENS * 0.001;
	GLfloat maxY = GetMaxY();
	glm::vec3 v1 = _distance;
    if (dPitch < 0) {
        dPitch = max(_upRotateAngle, dPitch);
    } else {
        dPitch = min((float)M_PI/2 - _upRotateAngle, dPitch);
    }
    _upRotateAngle -= dPitch;
	v1 = glm::rotate(v1, -dPitch, glm::cross(-_distance, constants::WORLD_UP));
    cout << "X" << " " << dYaw << endl;
    cout << "Y " << dPitch << endl;
	v1 = glm::rotate(v1, dYaw, constants::WORLD_UP);
	_distance.x = v1.x;
	_distance.y = v1.y;
	_distance.z = v1.z;
	_player.Rotate(dYaw, 0, 0);
}

// zoom is either -1 or 1
void FixedCamera::ChangeZoom(GLfloat zoom) {
	_distance += zoom * _distance * constants::ZOOM_FACTOR;
}
