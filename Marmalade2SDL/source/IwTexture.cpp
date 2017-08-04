#include "IwTexture.h"

CIwTexture::CIwTexture() : textureID(0), pixels(NULL), width(0), height(0), bpp(0), format(0)
{

}

CIwTexture::~CIwTexture()
{
	if (textureID != 0) glDeleteTextures(1, &textureID);
	if (pixels) delete pixels;
}

void CIwTexture::Serialise()
{
}

void CIwTexture::Resolve()
{
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

void CIwTexture::CopyFromBuffer(uint16_t w, uint16_t h, CIwImage::Format format, uint16_t pitch, uint8_t * pImageData, uint16_t * pPalette)
{
}

void CIwTexture::CopyFromImage(CIwImage * pImg)
{
}

void CIwTexture::SetImage(CIwImage * pImg)
{
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

CIwTexture * CIwTexture::ExtractSubTexture(uint16 x, uint16 y, uint16 w, uint16 h, const char * name)
{
	return nullptr;
}

void CIwTexture::ChangePalette(uint16 * pPalette, CIwImage::Format format)
{
}

void CIwTexture::SetModifiable(bool modify)
{
	//if (Surface) {
	//	if (modify) SDL_LockSurface(Surface); else SDL_UnlockSurface(Surface);
	//}
}

void CIwTexture::UseAsHandle(CIwTexture * pTex)
{
}

CIwTexture * CIwTexture::CloneWithNewPalette(const char * name, uint16 * pPalette)
{
	return nullptr;
}

CIwTexture * CIwTexture::UploadSubRegion(int u0, int v0, int u1, int v1)
{
	return nullptr;
}

void CIwTexture::PreparePalette(CIwImage * pImg)
{
}

bool CIwTexture::UsesTransparency(CIwImage * pImg, int32 threshhold)
{
	return false;
}

void CIwTexture::ReplaceTexture(CIwTexture * pTex)
{
}

void CIwTexture::ChangePalette(uint16 * pPalette)
{
}

void CIwTexture::ChangeTexels(uint8 * pTexels)
{
}

uint8* CIwTexture::GetTexels() const
{
	return pixels;
}

void CIwTexture::GetTexels(uint8 * pTexels, CIwImage::Format format) const
{
}

void CIwTexture::ChangeTexels(uint8* pTexels, CIwImage::Format format) {
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, pTexels);
}

void CIwTexture::RemakeMipmaps()
{
}

void CIwTexture::SetMipMapping(bool val)
{

}

void CIwTexture::SetClamping(bool bOn)
{
}

void CIwTexture::GetPalette(uint16 * pPalette, CIwImage::Format format) const
{
}

void CIwTexture::SetFiltering(bool val)
{

}

void CIwTexture::_FreeTexelData()
{
}

void CIwTexture::_FreePaletteData()
{
}

void CIwTexture::_SetTransparencyFlags(CIwImage * pImg, int threshhold)
{
}

void CIwTexture::_SetTransparencyFlags(int threshhold)
{
}

void CIwTexture::_Refresh()
{
}

void CIwTexture::SW_BindToSurface(s3eSurfaceInfo * pSurfaceInfo)
{
}

void CIwTexture::SW_ReleaseFromSurface()
{
}

CIwImage::Format CIwTexture::_DetermineFormatSW() const
{
	return CIwImage::Format();
}

void CIwTexture::_SetFormatFromImageTemplate()
{
}

void CIwTexture::_UpdateTexParamsGL(bool always)
{
}

uint16 * CIwTexture::_GetPaletteFromVRAM()
{
	return nullptr;
}

uint8 * CIwTexture::_GetTexelsFromVRAM()
{
	return nullptr;
}

uint16 * CIwTexture::_GetPaletteCopy()
{
	return nullptr;
}

uint8 * CIwTexture::_GetTexelsCopy()
{
	return nullptr;
}

uint32 CIwTexture::_GetTexelVRAMAddress()
{
	return uint32();
}

uint32 CIwTexture::_GetPaletteVRAMAddress() const
{
	return uint32();
}

int CIwTexture::GetActualColourDepth()
{
	return 0;
}

void CIwTexture::ColourReduce()
{
}

bool CIwTexture::IsSharedSource()
{
	return false;
}

bool CIwTexture::GetSharedForename(char * sharename, uint32 buffSize)
{
	return false;
}

void CIwTexture::CopySharedTexels()
{
}

void CIwTexture::GL_GetContents()
{
}

uint32 CIwTexture::_UploadIndividualImageGL(uint32 target, CIwImage & img)
{
	return uint32();
}

void CIwTexture::FreeCustomMipMaps()
{
}

void CIwTexture::FindSharedTexels()
{
}
