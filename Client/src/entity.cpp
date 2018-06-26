#include "constants.h"
#include "entity.h"

Entity::Entity(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll,
		GLfloat boundingBoxDeltaX,
		GLfloat boundingBoxDeltaY,
		GLfloat boundingBoxDeltaZ)
		: position(position)
		, front()
		, right()
		, up()
		, speed(speed)
		, yaw(yaw)
		, pitch(pitch)
		, roll(roll)
		, nextYaw(yaw)
		, nextPitch(pitch)
		, nextRoll(roll)
		, boundingBoxDeltaX(boundingBoxDeltaX)
		, boundingBoxDeltaY(boundingBoxDeltaY)
		, boundingBoxDeltaZ(boundingBoxDeltaZ) {
	CalculateBoundingBox();
	CalculateDirectionVectors();
}

Entity::~Entity() {}

// get rid of groundLevel just query that eventually when non-flat ground
void Entity::Tick(GLfloat deltaTime, GLfloat groundLevel) {
    AmbientMovement(deltaTime, groundLevel);
}

void Entity::AmbientMovement(GLfloat deltaTime, GLfloat groundLevel) {
	ambientMovement.y = ambientMovement.y + constants::GRAVITY * deltaTime;
	position.y += ambientMovement.y * deltaTime;
	if (position.y - boundingBoxDeltaY < groundLevel) {
		position.y = groundLevel + boundingBoxDeltaY;
		grounded = true;
        if (recoiling) {
            recoiling = false;
            ambientMovement = glm::vec3();
        }
	}
    position.x += ambientMovement.x * deltaTime; 
    position.z += ambientMovement.z * deltaTime; 
}

void Entity::Move(EntityMovement direction, GLfloat delta) {
	CalculateDirectionVectors();
	GLfloat velocity = delta * speed;
	position += front * velocity;
}

void Entity::Rotate(GLfloat yaw, GLfloat pitch, GLfloat roll) {
	nextYaw += yaw;
	nextPitch += pitch;
	nextRoll += roll;
}

void Entity::Jump(float yVel) {
	if (grounded) {
		grounded = false;
		ambientMovement.y = yVel;
	}
}

void Entity::CalculateDirectionVectors() {
	yaw = nextYaw;
	pitch = nextPitch;
	roll = nextRoll;
	front.x = -cos(yaw);
	front.y = sin(pitch);
	front.z = sin(yaw) * cos(pitch);
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, constants::WORLD_UP));
	up = glm::normalize(glm::cross(right, front));
}

void Entity::CalculateBoundingBox() {
	glm::vec3 corner1(-boundingBoxDeltaX, boundingBoxDeltaY, boundingBoxDeltaZ);
	glm::vec3 corner2(boundingBoxDeltaX, boundingBoxDeltaY, -boundingBoxDeltaZ);
	glm::vec3 corner3(-boundingBoxDeltaX, -boundingBoxDeltaY, -boundingBoxDeltaZ);
	glm::vec3 corner4(boundingBoxDeltaX, -boundingBoxDeltaY, boundingBoxDeltaZ);
	std::vector<glm::vec3> corners{ corner1, corner2, corner3, corner4 };
	for (const auto& corner : corners) {
		bbEdges.emplace_back(
			corner,
			corner + (corner.x > 0 ? -1 : 1) * 2 * boundingBoxDeltaX);
		bbEdges.emplace_back(
			corner,
			corner + (corner.y > 0 ? -1 : 1) * 2 * boundingBoxDeltaY);
		bbEdges.emplace_back(
			corner,
			corner + (corner.z > 0 ? -1 : 1) * 2 * boundingBoxDeltaZ);
	}
	for (int i = -1; i <= 1; i += 2) {
		for (int j = -1; j <= 1; j += 2) {
			for (int k = -1; k <= 1; k += 2) {
				bbCorners.emplace_back(
					i * boundingBoxDeltaX,
					j * boundingBoxDeltaY,
					k * boundingBoxDeltaZ);
			}
		}
	}
}
