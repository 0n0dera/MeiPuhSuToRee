#include "world.h"
#include "constants.h"
#include "util.h"

World::World()
		: player(constants::WORLD_CENTER, constants::MED_SPEED)
		, camera(player)
		, other()
		, _playerVAO()
		, _playerVBO()
		, _playerEBO()
		, _playerShader()
		, _playerNumVertices()
		, _groundVAO()
		, _groundVBO()
		, _groundEBO()
		, _groundNumVertices()
		, _groundLevel()
		, _view()
		, _projection() {
	init();
}

World::~World()
{
	glDeleteVertexArrays(1, &_playerVAO);
	glDeleteBuffers(1, &_playerVBO);
}

void World::init()
{
	other.emplace_back(glm::vec3(10, 0, 10), constants::MED_SPEED);	
	initPlayerData();
	initGroundData();
}

void World::initPlayerData() {
	// Create Shader
	_playerShader = util::genShader("player.vs", "player.frag");

	GLfloat player_vertices[] = {
		// Positions 
		-constants::PLAYER_BB_X, -constants::PLAYER_BB_Y, -constants::PLAYER_BB_Z, 1.0f, 0.0f, 0.0f,
		constants::PLAYER_BB_X, -constants::PLAYER_BB_Y, -constants::PLAYER_BB_Z, 1.0f, 0.0f, 0.0f,
		constants::PLAYER_BB_X,  constants::PLAYER_BB_Y, -constants::PLAYER_BB_Z, 1.0f, 0.0f, 0.0f,
		-constants::PLAYER_BB_X,  constants::PLAYER_BB_Y, -constants::PLAYER_BB_Z, 1.0f, 1.0f, 0.0f,
		-constants::PLAYER_BB_X, -constants::PLAYER_BB_Y,  constants::PLAYER_BB_Z, 0.0f, 1.0f, 1.0f,
		constants::PLAYER_BB_X, -constants::PLAYER_BB_Y,  constants::PLAYER_BB_Z, 0.0f, 1.0f, 0.0f,
		constants::PLAYER_BB_X,  constants::PLAYER_BB_Y,  constants::PLAYER_BB_Z, 0.0f, 1.0f, 0.0f,
		-constants::PLAYER_BB_X,  constants::PLAYER_BB_Y,  constants::PLAYER_BB_Z, 0.0f, 1.0f, 0.0f,
	};
	unsigned int player_indices[] = {
		0, 3, 1,
		1, 3, 2,
		3, 7, 2,
		2, 7, 6,
		4, 7, 5,
		5, 7, 6,
		0, 4, 1,
		1, 4, 5,
		1, 2, 5,
		2, 5, 6,
		0, 4, 3,
		4, 3, 7
	};

	_playerNumVertices = sizeof(player_indices) / sizeof(unsigned int);
	// gen player VAO
	glGenVertexArrays(1, &_playerVAO);
	glBindVertexArray(_playerVAO);

	// gen player VBO
	glGenBuffers(1, &_playerVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _playerVBO);
	// Whatever object is currently bound to GL_ARRAY_BUFFER manages the vertices data
	glBufferData(GL_ARRAY_BUFFER, sizeof(player_vertices), player_vertices, GL_STATIC_DRAW);
	// Link vertex attributes. Configurations will apply to currently bound VBO and VAO
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	// gen player EBO
	glGenBuffers(1, &_playerEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _playerEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(player_indices), player_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void World::initGroundData() {
	// right now ground is just a square
	GLfloat vertices[] = {
		// Positions 
		// bottom left
		-10.0f, 0.0f, -10.0f, 1.0f, 1.0f, 1.0f,
		//top left
		-10.0f, 0.0f, 10.0f, 1.0f, 1.0f, 1.0f,
		// bottom right
		10.0f, 0.0f, -10.0f, 1.0f, 1.0f, 1.0f,
		// top right
		10.0f, 0.0f, 10.0f, 1.0f, 1.0f, 1.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	_groundNumVertices = sizeof(indices) / sizeof(unsigned int);
	// gen player VAO
	glGenVertexArrays(1, &_groundVAO);
	glBindVertexArray(_groundVAO);

	// gen player VBO
	glGenBuffers(1, &_groundVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _groundVBO);
	// Whatever object is currently bound to GL_ARRAY_BUFFER manages the vertices data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Link vertex attributes. Configurations will apply to currently bound VBO and VAO
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	// gen player EBO
	glGenBuffers(1, &_groundEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _groundEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void World::Tick(GLfloat deltaTime) {
	player.Tick(deltaTime, _groundLevel);
}

void World::Draw()
{
	_view = camera.GetViewMatrix();
	_projection = glm::perspective(camera.Zoom(), constants::WIDTH / constants::HEIGHT, 0.1f, 100.0f);
	for (auto& p : other) {
		DrawPlayer(p);
	}
	DrawPlayer(player);
	DrawGround();
}

void World::DrawPlayer(const Player& player) {
	glUseProgram(_playerShader);

	glm::mat4 model;
	model = glm::translate(model, player.position);
	model = glm::rotate(model, player.yaw, constants::Y_AXIS);
	model = glm::rotate(model, player.pitch, constants::X_AXIS);
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "view"), 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	glBindVertexArray(_playerVAO);
	glDrawElements(GL_TRIANGLES, _playerNumVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void World::DrawGround() {
	glUseProgram(_playerShader);

	glm::mat4 model;
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "view"), 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	glBindVertexArray(_groundVAO);
	glDrawElements(GL_TRIANGLES, _groundNumVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}