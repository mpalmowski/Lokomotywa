#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertex.hpp"
#include "Texture.hpp"

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	Display* display = new Display(WIDTH, HEIGHT);

	Vertex vertices[] =
	{
		Vertex(-0.5, -0.5, 0, 0.0, 0.0),
		Vertex(0, 0.5, 0, 0.5, 1.0),
		Vertex(0.5, -0.5, 0, 1.0, 0.0)
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("shader");

	Texture texture;
	texture.loadRGB("rusted_steel.png");

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(1.0f, 1.0f, 1.0f, 1.0f);

		shader.bind();
		texture.bind(0);
		mesh.draw();

		display->swapBuffers();
	}

	delete display;
}
