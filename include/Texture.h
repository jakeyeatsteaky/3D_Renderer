#ifndef TEXTURE_H
#define TEXTURE_H
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