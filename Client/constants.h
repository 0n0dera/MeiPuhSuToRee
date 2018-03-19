#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <GL/glew.h>

namespace constants {
/*
 * WINDOW CONSTANTS
 */
// width/height of screen
const GLfloat WIDTH = 800;
const GLfloat HEIGHT = 600;

/*
 * PLAYER CONSTANTS
 */
const GLfloat PLAYER_BB_X = 0.5f;
const GLfloat PLAYER_BB_Y = 1.0f;
const GLfloat PLAYER_BB_Z = 0.5f;


/*
 * ENTITY CONSTANTS
 */
// movement speeds
const GLfloat LOW_SPEED = 2.0f;
const GLfloat MED_SPEED = 5.0f;
const GLfloat HIGH_SPEED = 8.0f;

const GLfloat FORWARD_YAW = -glm::half_pi<GLfloat>();
/*
 * WORLD CONSTANTS
 */
const GLfloat GRAVITY = -9.8;
const glm::vec3 WORLD_CENTER = { 0.0f, 0.0f, 0.0f };
const glm::vec3 X_AXIS = { 1.0f, 0.0f, 0.0f };
const glm::vec3 Y_AXIS = { 0.0f, 1.0f, 0.0f };
const glm::vec3 Z_AXIS = { 0.0f, 0.0f, 1.0f };
const glm::vec3 LOOK_FORWARD = { 0.0f, 0.0f, -1.0f };
const glm::vec3 LOOK_BEHIND = { 0.0f, 0.0f, 1.0f };
// up unit vector for the world
const glm::vec3 WORLD_UP = { 0.0f, 1.0f, 0.0f };

/*
 *  CAMERA CONSTANTS
 */
// mouse sensitivity
const GLfloat MOUSE_SENS = 0.001f;
// camera constant distance from player
const GLfloat CAMERA_DISTANCE = 5.0f;
// initial camera zoom
const GLfloat CAMERA_ZOOM = 45.0f;
// zoom factor as we inc/dec zoom
const GLfloat ZOOM_FACTOR = 0.05f;
}