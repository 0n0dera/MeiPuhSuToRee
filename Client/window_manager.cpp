#include "window_manager.h"

WindowManager::WindowManager(GLuint width, const GLuint height)
	:WIDTH(width), HEIGHT(height), window(nullptr)
{
	init();
}

WindowManager::~WindowManager()
{
	glfwTerminate();
}

GLFWwindow* WindowManager::GetWindow()
{
	return window;
}

void WindowManager::init()
{
	// Initialization
	glfwInit();
	// OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Using core OpenGL, so no deprecated functions can be used
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// GLFW - create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// GLEW - initialize
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

