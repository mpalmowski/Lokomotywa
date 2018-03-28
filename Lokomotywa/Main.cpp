#include "Display.hpp"
#include "Shader.h"
#include "Mesh.hpp"
#include "Vertex.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

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

	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	Transform transform;

	while (!display->windowShouldClose())
	{
		display->checkEvents();

		display->clearColor(0.2f, 0.2f, 1.0f, 1.0f);

		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		mesh.draw();

		display->swapBuffers();
	}

	delete display;
}
