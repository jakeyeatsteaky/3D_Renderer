#include "Texture.h"
#include <iostream>
#include <cstring>
#define GLEW_STATIC 
#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture(const char* pathToTexture, Extension_Type exType)
{
	switch (exType)
	{
	case Extension_Type_JPG: {
		unsigned char* data = stbi_load(pathToTexture, &m_width, &m_height, &m_numChannels, 0);
		if (data)
		{
			glGenTextures(1, &m_texIdx);
			glBindTexture(GL_TEXTURE_2D, m_texIdx);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
	
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		break;
	}

	case Extension_Type_PNG: {
		unsigned char* data = stbi_load(pathToTexture, &m_width, &m_height, &m_numChannels, 0);
		if (data)
		{
			glGenTextures(1, &m_texIdx);
			glBindTexture(GL_TEXTURE_2D, m_texIdx);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		break;
	}
	
	}
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texIdx);
}