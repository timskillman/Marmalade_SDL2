#include "IwTexture.h"

CIwTexture::CIwTexture() : textureID(0), pixels(NULL), width(0), height(0), bpp(0), format(0)
{

}

CIwTexture::~CIwTexture()
{
	if (textureID != 0) glDeleteTextures(1, &textureID);
	if (pixels) delete pixels;
}

void CIwTexture::LoadFromFile(const char* file)
{
	textureID = 0;

	SDL_Surface* Surface = IMG_Load(file);
	if (Surface == NULL)
		SDL_ShowSimpleMessageBox(0, "Load image error", IMG_GetError(), NULL);
	if (Surface) {
		size = Surface->h*Surface->pitch;
		pixels = new uint8_t[size];  //new GLubyte[width*height]()
		if (pixels) {

			memcpy(pixels, Surface->pixels, size);

			bpp = Surface->format->BytesPerPixel;
			format = GL_RGB;
#ifdef WIN32
			if (bpp == 4) format = GL_RGBA;
#endif
#ifdef __APPLE__
			if (bpp == 4) format = GL_BGRA;
#endif
			width = Surface->w;
			height = Surface->h;
		}
		SDL_FreeSurface(Surface);
	}
}

void CIwTexture::Upload()
{
	if (textureID == 0 && pixels) {
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
}

void CIwTexture::ChangeTexels(uint8* pTexels, CIwImage::Format format) {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, pTexels);
}

