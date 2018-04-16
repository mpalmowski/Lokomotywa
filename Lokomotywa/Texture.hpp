#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <GL/glew.h>
#include <SOIL.h>

struct Texture
{
	GLuint texture;

	~Texture()
	{
		glDeleteTextures(1, &texture);
	}

	void loadRGB(const std::string &filename)
	{
		std::string file_location = "textures/" + filename;

		int width, height;
		unsigned char* image = SOIL_load_image(file_location.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
			std::cerr << "Failed to load texture file: " << filename << std::endl;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void loadRGBA(const std::string &filename)
	{
		std::string file_location = "textures/" + filename;

		int width, height;
		unsigned char* image = SOIL_load_image(file_location.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		if (image == nullptr)
			std::cerr << "Failed to load texture file: " << filename << std::endl;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void bind(unsigned int texture_unit)
	{
		while (texture_unit < 0)
			texture_unit += 31;

		while (texture_unit > 31)
			texture_unit -= 31;

		if (texture_unit < 0 || texture_unit > 31)
			std::cerr << "Texture unit out of range: " << texture_unit << std::endl;

		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void unbind(unsigned int texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif