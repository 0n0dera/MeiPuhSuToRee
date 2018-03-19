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
	CalculateDirectionVectors();
}

Entity::~Entity() {}

void Entity::Tick(GLfloat deltaTime, GLfloat groundLevel) {
	yVelocity = yVelocity + constants::GRAVITY * deltaTime;
	position.y += yVelocity * deltaTime;
	if (position.y - boundingBoxDeltaY < groundLevel) {
		position.y = groundLevel + boundingBoxDeltaY;
		grounded = true;
		yVelocity = 0.0f;
	}
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

void Entity::Jump() {
	if (grounded) {
		grounded = false;
		yVelocity = 5.0f;
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