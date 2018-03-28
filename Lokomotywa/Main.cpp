#include "Display.hpp"
#include "Shader.h"
#include "Mesh.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

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

	Transform transform;

	float angle = 0;

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(0.2f, 0.2f, 1.0f, 1.0f);

		shader.bind();
		texture.bind(0);
		shader.update(transform);
		mesh.draw();

		display->swapBuffers();

		angle += 0.001;
		transform.rotation.x = angle;
	}

	delete display;
}
