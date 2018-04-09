#include "collision_detector.h"

Entity* CollisionDetector::collide(const Entity& entity, const std::vector<Entity*>& candidates) {
	for (const auto& e : candidates) {
		// check if entity corner in candidate
		for (const auto& corner : entity.bbCorners) {
			glm::vec3 actual(corner + entity.position);
			if (cornerInEntity(actual, *e)) {
				return e;
			}
		}
		// check if candidate corner in entity
		for (const auto& corner : e->bbCorners) {
			glm::vec3 actual(corner + e->position);
			if (cornerInEntity(actual, entity)) {
				return e;
			}
		}
	}
	return nullptr;
}

bool CollisionDetector::cornerInEntity(const glm::vec3& corner, const Entity& entity) const {
	return (entity.position.x - entity.boundingBoxDeltaX <= corner.x &&
		corner.x <= entity.position.x + entity.boundingBoxDeltaX &&
		entity.position.y - entity.boundingBoxDeltaY <= corner.y &&
		corner.y <= entity.position.y + entity.boundingBoxDeltaY &&
		entity.position.z - entity.boundingBoxDeltaZ <= corner.z &&
		corner.z <= entity.position.z + entity.boundingBoxDeltaZ);
}