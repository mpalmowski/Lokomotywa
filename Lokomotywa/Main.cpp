#include "Display.hpp"
#include "Shader.h"
#include "Camera.hpp"
#include "Locomotive.hpp"
#include <chrono>

const float ROT_ANGLE = 0.03;
const float RAD_STEP = 0.1;
const float LIGHT_STEP = 0.05;
Camera *camera = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/**
	 * Sterowanie:
	 *	strza³ki - poruszanie kamery wokó³ obiektu
	 *	w, s - kamera bli¿ej/dalej obiektu
	 *	z, x - oœwietlenie punktowe +/-
	 */
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
		case GLFW_KEY_Z:
			camera->adjustLight(-LIGHT_STEP);
			break;
		case GLFW_KEY_X:
			camera->adjustLight(LIGHT_STEP);
			break;
		}
	}
}

int main()
{
	Display* display = new Display(&key_callback);

	camera = new Camera(12, (float)WIDTH / (float)HEIGHT);
	Shader shader("shader");

	Locomotive *locomotive = new Locomotive();

	int fps = 0;
	auto start = std::chrono::system_clock::now();
	auto now = start;
	std::chrono::duration<double> duration;

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(0.3f, 0.3f, 0.3f, 1.0f);

		locomotive->draw(shader, *camera);

		display->swapBuffers();

		fps++;
		now = std::chrono::system_clock::now();
		duration = now - start;
		if(duration.count() > 1)
		{
			std::cout << "FPS: " << fps << std::endl;
			start = std::chrono::system_clock::now();
			fps = 0;
		}
	}

	delete display;
	delete camera;
	delete locomotive;
}
