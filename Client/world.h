#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "fixed_camera.h"
#include "player.h"

class World
{
public:
	World();
	~World();
	void Draw();

	Player player;
	FixedCamera camera;
	std::vector<Player> other;
private:
	void DrawPlayer(const Player& player, const glm::mat4& view, const glm::mat4& projection);
	void init();

	GLuint _playerVAO;
	GLuint _playerVBO;
	GLuint _playerEBO;
	GLuint _playerShader;
	int _playerNumVertices;
};