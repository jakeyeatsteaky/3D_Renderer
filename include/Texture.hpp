#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include "enumerations.h"

class Texture
{
public:
	Texture() = default;
	Texture(const char* pathToTexture, Extension_Type exType);

	void Bind();


private:
	unsigned int m_texIdx;
	int m_width;
	int m_height;
	int m_numChannels;
};



#endif