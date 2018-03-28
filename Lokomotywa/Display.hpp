#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC

#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

class Display
{
private:
	GLFWwindow* window;
	int width, height;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		cout << key << endl;
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

public:
	bool windowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	Display(GLuint width, GLuint height) : width(width), height(height)
	{
		if (glfwInit() != GL_TRUE)
		{
			cout << "GLFW initialization failed" << endl;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		try
		{
			window = glfwCreateWindow(this->width, this->height, "GKOM - OpenGL 01", nullptr, nullptr);
			if (window == nullptr)
				throw exception("GLFW window not created");
			glfwMakeContextCurrent(window);
			glfwSetKeyCallback(window, key_callback);

			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
				throw exception("GLEW Initialization failed");

			glViewport(0, 0, this->width, this->height);
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
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
	}
};

#endif // DISPLAY_H