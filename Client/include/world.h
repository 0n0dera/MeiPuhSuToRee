#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "collision_detector.h"
#include "fixed_camera.h"
#include "player.h"

class World
{
public:
	World();
	~World();
	void Tick(GLfloat delta);
	void Draw();

	Player player;
	FixedCamera camera;
	CollisionDetector collisionDetector;
	std::vector<Entity*> enemies;
private:
	// drawing functions
	void DrawPlayer(const Player& player);
	void DrawEnemies();
	void DrawGround();
	void init();
	void initPlayerData();
	void initGroundData();

	// player data
	GLuint _playerVAO;
	GLuint _playerVBO;
	GLuint _playerEBO;
	GLuint _playerShader;
	int _playerNumVertices;

	// ground data
	GLuint _groundVAO;
	GLuint _groundVBO;
	GLuint _groundEBO;
	int _groundNumVertices;
	GLfloat _groundLevel;

	// view/projection matrices
	glm::mat4 _view;
	glm::mat4 _projection;
};
