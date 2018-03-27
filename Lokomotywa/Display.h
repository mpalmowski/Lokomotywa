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

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	bool windowShouldClose();

	Display(GLuint width, GLuint height);

	~Display();

	void swapBuffers();

	void checkEvents();

	void clearColor(float r, float g, float b, float a);
};

#endif // DISPLAY_H