#include "Display.hpp"
#include "Shader.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Figures.h"

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	Display* display = new Display(WIDTH, HEIGHT);

	Vertices vertices = *createRingPolygon(80, -0.1, 0.7);
	vertices += *createRingPolygon(80, 0.1, 0.7);
	Mesh mesh(vertices);

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

		transform.rotation.z += 0.001;
		camera.moveHorizontallyByAngle(0.0005);
	}

	delete display;
}
