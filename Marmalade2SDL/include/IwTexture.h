#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "s3e.h"
#include "IwImage.h"
#include "s3eTypes.h"
#include "CIwVector.h"

class CIwTexture
{
public:

	CIwTexture();
	~CIwTexture();

	void    LoadFromFile(const char* imageFile);
	void    ChangeTexels(uint8* pTexels, CIwImage::Format format);
	void	Upload();

	uint32_t textureID;
private:
	uint8_t* pixels;
	int bpp;
	int format;
	int width;
	int height;
	size_t size;

};