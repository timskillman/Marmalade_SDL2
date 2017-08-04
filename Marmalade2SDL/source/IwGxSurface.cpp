#include "IwGxSurface.h"

CIwGxSurface::CIwGxSurface() //TODO
{
	m_surface = nullptr;
	m_State = UNCREATED;
}

CIwGxSurface::~CIwGxSurface() //TODO
{
}

bool CIwGxSurface::CreateSurface(CIwTexture * pTexture, uint32_t width, uint32_t height, uint32_t usage) //TODO
{
	m_HW_SurfaceInfo.m_Data = pTexture->GetTexels();
	m_HW_SurfaceInfo.m_Width = width;
	m_HW_SurfaceInfo.m_Height = height;
	m_HW_SurfaceInfo.m_Pitch = pTexture->GetPitch();
	
	uint32_t rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	int shift = (req_format == STBI_rgb) ? 8 : 0;
	rmask = 0xff000000 >> shift;
	gmask = 0x00ff0000 >> shift;
	bmask = 0x0000ff00 >> shift;
	amask = 0x000000ff >> shift;
#else // little endian, like x86
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	m_surface = SDL_CreateRGBSurfaceFrom(m_HW_SurfaceInfo.m_Data, width, height, pTexture->GetDepth(), m_HW_SurfaceInfo.m_Pitch, rmask, gmask, bmask, amask);
	m_State = CREATED;
	return true;
}

bool CIwGxSurface::RecreateSurface(uint32_t width, uint32_t height) //TODO
{
	return false;
}

void CIwGxSurface::MakeCurrent() //TODO
{
}

void CIwGxSurface::MakeDisplayCurrent() //TODO
{
}

const CIwFVec2 & CIwGxSurface::GetClientUVExtentFloat() //TODO
{
	CIwFVec2 a(0, 0);
	return a;
}

uint32_t CIwGxSurface::GetWidth() //TODO
{
	return m_HW_SurfaceInfo.m_Width;
}

uint32_t CIwGxSurface::GetHeight() //TODO
{
	return m_HW_SurfaceInfo.m_Height;
}

uint32_t CIwGxSurface::GetClientWidth() //TODO
{
	return uint32_t();
}

uint32_t CIwGxSurface::GetClientHeight() //TODO
{
	return uint32_t();
}

bool CIwGxSurface::HasAlphaChannel() //TODO
{
	return false;
}

CIwGxSurface::CIwGxSurfaceImplementation CIwGxSurface::GetImplementation() //TODO
{
	return CIwGxSurfaceImplementation();
}

const s3eSurfaceInfo & CIwGxSurface::GetSurfaceInfo() //TODO
{
	// TODO: insert return statement here
	return m_HW_SurfaceInfo;
}

void CIwGxSurface::BindSurface() //TODO
{
}

void CIwGxSurface::ReleaseSurface() //TODO
{
}

void CIwGxSurface::DestroySurface() //TODO
{
}
