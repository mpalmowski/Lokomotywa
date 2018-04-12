#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC

#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int WIDTH = 1280, HEIGHT = 720;

class Display
{
private:
	GLFWwindow* window;

public:

	int windowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	void setLight()
	{
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
		GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
		GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

		GLfloat qaLightPosition[] = { 0.5, 0.5, 0.0, 1.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

		GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 };
		GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 };
		glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
		glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
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
		glEnable(GL_NORMALIZE);

		//setLight();
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