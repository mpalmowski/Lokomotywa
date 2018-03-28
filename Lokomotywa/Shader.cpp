#include "Shader.h"

Shader::Shader(const std::string& filename)
{
	program = glCreateProgram();
	shaders[0] = createShader(loadShader(filename + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = createShader(loadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texture_position");

	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Program linking failed");

	glValidateProgram(program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Program is invalid");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::bind()
{
	glUseProgram(program);
}

std::string Shader::loadShader(const std::string& filename)
{
	std::ifstream file;
	file.open((filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

GLuint Shader::createShader(const std::string& text, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);

	if (shader == 0)
		std::cerr << "Error: compiling shader type " << shader_type << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool is_program, const std::string& error_message)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (is_program)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (is_program)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << "Error: " << error_message << ": '" << error << "'" << std::endl;
	}
}
