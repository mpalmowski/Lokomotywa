#include "Display.h"
#include "Shader.h"

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	Display* display = new Display(WIDTH, HEIGHT);

	Shader shader("shader");

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(0.1f, 0.2f, 0.3f, 1.0f);

		shader.bind();

		display->swapBuffers();
	}

	delete display;
}
