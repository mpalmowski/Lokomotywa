#ifndef RENDERED_OBJECT_HPP
#define RENDERED_OBJECT_HPP

class RenderedObject
{
private:
	Vertices vertices;
	Mesh *mesh;
	Texture texture;
	Transform transform;
public:
	RenderedObject(Vertices &vertices, const std::string &texture_file): vertices(vertices)
	{
		mesh = new Mesh(vertices);

		texture.loadRGB(texture_file);
	}

	~RenderedObject()
	{
		delete mesh;
	}

	void moveBy(float x, float y, float z)
	{
		transform.position.x += x;
		transform.position.y += y;
		transform.position.z += z;
	}

	void rotateBy(float x, float y, float z)
	{
		transform.rotation.x += x;
		transform.rotation.y += y;
		transform.rotation.z += z;
	}

	void draw(unsigned int texture_unit, Shader &shader, Camera &camera)
	{
		shader.bind();
		texture.bind(0);
		shader.update(transform, camera);
		mesh->draw();
	}
};

#endif