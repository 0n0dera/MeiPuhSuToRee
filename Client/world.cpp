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
		, _playerNumVertices() {
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
	// Create Shader
	_playerShader = util::genShader("player.vs", "player.frag");

	GLfloat player_vertices[] = {
		// Positions 
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
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

	_playerNumVertices = sizeof(player_indices) / sizeof(GLuint);
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

void World::Draw()
{
	glm::mat4 view, projection;
	view = camera.GetViewMatrix();
	projection = glm::perspective(camera.Zoom(), constants::WIDTH / constants::HEIGHT, 0.1f, 100.0f);
	for (auto& p : other) {
		DrawPlayer(p, view, projection);
	}
	DrawPlayer(player, view, projection);
}

void World::DrawPlayer(const Player& player, const glm::mat4& view, const glm::mat4& projection) {
	glUseProgram(_playerShader);

	glm::mat4 model;
	model = glm::translate(model, player.Position());
	model = glm::rotate(model, player.Yaw(), constants::Y_AXIS);
	model = glm::rotate(model, player.Pitch(), constants::X_AXIS);
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(_playerShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(_playerVAO);
	glDrawElements(GL_TRIANGLES, _playerNumVertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

