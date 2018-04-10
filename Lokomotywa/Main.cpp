#include "Display.hpp"
#include "Shader.h"
#include "Camera.hpp"
#include "Locomotive.hpp"

const float ROT_ANGLE = 0.03;
const float RAD_STEP = 0.03;
Camera *camera = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_RIGHT:
			camera->moveHorizontallyByAngle(ROT_ANGLE);
			break;
		case GLFW_KEY_LEFT:
			camera->moveHorizontallyByAngle(-1 * ROT_ANGLE);
			break;
		case GLFW_KEY_UP:
			camera->moveVerticallyByAngle(-1 * ROT_ANGLE);
			break;
		case GLFW_KEY_DOWN:
			camera->moveVerticallyByAngle(ROT_ANGLE);
			break;
		case GLFW_KEY_W:
			camera->moveAlongRadius(-1 * RAD_STEP);
			break;
		case GLFW_KEY_S:
			camera->moveAlongRadius(RAD_STEP);
			break;
		}
	}
}

int main()
{
	Display* display = new Display(&key_callback);

	camera = new Camera(9, (float)WIDTH / (float)HEIGHT);
	Shader shader("shader");

	Locomotive *locomotive = new Locomotive();

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(0.3f, 0.3f, 0.3f, 1.0f);

		locomotive->draw(shader, *camera);

		display->swapBuffers();
	}

	delete display;
	delete camera;
	delete locomotive;
}
