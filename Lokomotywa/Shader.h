#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include "Transform.hpp"
#include "Camera.hpp"

class Shader
{
private:
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	static const unsigned int NUM_SHADERS = 2;
	GLuint program;
	GLuint shaders[NUM_SHADERS];
	GLuint uniforms[NUM_UNIFORMS];

	static void checkShaderError(GLuint shader, GLuint flag, bool is_program, const std::string &error_message);
	static std::string loadShader(const std::string &filename);
	static GLuint createShader(const std::string &text, GLenum shader_type);
public:
	Shader(const std::string &filename);
	~Shader();
	void bind();
	void update(const Transform &transform, const Camera &camera);
};

#endif SHADER_H