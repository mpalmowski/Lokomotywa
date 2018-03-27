#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertex.hpp"

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	Display* display = new Display(WIDTH, HEIGHT);

	Vertex vertices[] =
	{
		Vertex(-0.5, -0.5, 0),
		Vertex(0, 0.5, 0),
		Vertex(0.5, -0.5, 0)
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("shader");

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(1.0f, 1.0f, 1.0f, 1.0f);

		shader.bind();
		mesh.draw();

		display->swapBuffers();
	}

	delete display;
}
