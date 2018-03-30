#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC

#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const GLuint WIDTH = 800, HEIGHT = 600;

class Display
{
private:
	GLFWwindow* window;

public:

	int windowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	Display(GLFWkeyfun key_callback)
	{
		if (glfwInit() != GL_TRUE)
		{
			std::cout << "GLFW initialization failed" << std::endl;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		try
		{
			window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 01", nullptr, nullptr);
			if (window == nullptr)
				throw std::exception("GLFW window not created");
			glfwMakeContextCurrent(window);
			glfwSetKeyCallback(window, key_callback);

			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
				throw std::exception("GLEW Initialization failed");

			glViewport(0, 0, WIDTH, HEIGHT);
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
	}

	~Display()
	{
		glfwTerminate();
	}

	void swapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void checkEvents()
	{
		glfwPollEvents();
	}

	void clearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
};

#endif // DISPLAY_H