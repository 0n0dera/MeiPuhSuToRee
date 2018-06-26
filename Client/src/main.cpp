// includes
#include <iostream>
// GLEW
#include <GL/glew.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// header includes
#include "window_manager.h"
#include "world.h"

void do_movement(GLfloat deltaTime, World& world);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos);
void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024];
double last_x = constants::WIDTH / 2, last_y = constants::HEIGHT / 2;

int main() {
	WindowManager window_manager;
	GLFWwindow* window = window_manager.GetWindow();

	// Set key callback
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_DEPTH_TEST);

	World world;
	glfwSetWindowUserPointer(window, &world);

	while (!glfwWindowShouldClose(window)) {
		//network.SendPositionInfo(scene.player);
		//network.ReceiveInfo(scene);
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Events
		glfwPollEvents();
		do_movement(deltaTime, world);
		// Render
		// Set clear color
		glClearColor(0.1f, 0.3f, 0.5f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		world.Tick(deltaTime);
		world.Draw();

		// Swap buffer
		glfwSwapBuffers(window);
	}

	return 0;
}

void do_movement(GLfloat deltaTime, World& world)
{
	if (keys[GLFW_KEY_W])
	{
		world.player.Move(Player::FORWARD, deltaTime);
	}
	else if (keys[GLFW_KEY_S])
	{
		world.player.Move(Player::BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A])
	{
		world.player.Move(Player::LEFT, deltaTime);
	}
	else if (keys[GLFW_KEY_D])
	{
		world.player.Move(Player::RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_SPACE]) {
		world.player.Jump();
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
	{
		keys[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		keys[key] = false;
	}
}

bool first_mouse = true;
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	World* world = reinterpret_cast<World*>(glfwGetWindowUserPointer(window));
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}
	world->camera.Rotate(x_pos - last_x, y_pos - last_y);
	last_x = x_pos;
	last_y = y_pos;
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	World* world = reinterpret_cast<World*>(glfwGetWindowUserPointer(window));
	world->camera.ChangeZoom(-y_offset);
}
