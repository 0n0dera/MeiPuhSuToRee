#pragma once
#include <vector>
#include "entity.h"
#include "player.h"


class CollisionDetector {
public:
	Entity* collide(const Entity& entity, const std::vector<Entity*>& candidates);
private:
	bool cornerInEntity(const glm::vec3& corner, const Entity& entity) const;
};