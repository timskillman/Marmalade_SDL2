#pragma once

#include "s3eTypes.h"
#include "s3eSurface.h"
#include "CIwVector.h"
#include "IwTexture.h"

#define IW_GX_SURFACE_MIN_SIZE 16
#define IW_GX_SURFACE_SW_MAX_SIZE 512

class CIwGxSurface
{
public:
	//-------------------------------------------------------------------------
	// Public API
	//-------------------------------------------------------------------------
	/**
	* Constructor.
	*/
	CIwGxSurface();

	/**
	* Destructor.
	*/
	~CIwGxSurface();

	/**
	* Surface usage flags
	*/
	enum
	{
		EXACT_MATCH_F = (1 << 0), //!< Get a surface which exactly matches the size. If a surface this size cannot be created the largest possible surface with the same aspect ratio will be created.
		ALPHA_F = (1 << 1), //!< Get a surface with an alpha channel. It may not be possible to create a surface with an alpha channel, if so the resulting will return false from HasAlphaChannel().
		PERSISTENT_F = (1 << 2), //!< Get a surface which has a persistent state. Surface creation will fail if not available.
		FREE_ASPECT_F = (1 << 3), //!< Allow any aspect ratio... default will match aspect in width/height creation arguments.
		PRESERVE_FRAME_BUFFER_F = (1 << 4), //!< Selecting this surface must not invalidate the frame buffer. Surface creation will fail if not available.
		CREATE_565_SURFACE_F = (1 << 5), //!< Get a surface that has a RGB565 surface pixel type.
		CREATE_8888_SURFACE_F = (1 << 6), //!< Get a surface that has an ARGB8888 surface pixel type.
		DEPTH_BUFFER_IS_TEXTURE_F = (1 << 7), //!< The depth buffer is a texture not a buffer
		DEPTH_BUFFER_IS_32_BIT_F = (1 << 8), //!< The depth buffer is 32 bit rather than 16 bit
	};

	/**
	* Underlying surface implementation
	*/
	enum CIwGxSurfaceImplementation
	{
		SW,                                     //!< SW renderer surface. Surface switches are cheap.
		CTI,                                    //!< EGL1.0 glCopyTexImage using frame buffer. Surface switches require a copy of the surface, making them expensive for larger surfaces. NB. If PERSISTENT_F is set, a copy is required on MakeCurrent also.
		EGL_10,                                 //!< EGL1.0 glCopyTexImage using 'real' surface. Surface switches require a copy of the surface, making them expensive for larger surfaces.
		EGL_11,                                 //!< EGL1.1 glBindTexImage using 'real' surface. Surface switches should not require a copy of the surface. However context switches are still generally fairly expensive.
		FBO_OES,                                //!< GL1.x Frame Buffer Object via GL_OES_framebuffer_object extension. Surface switches should be cheap, but in practise it varies from driver to driver.
		FBO,                                    //!< GL2.0 Frame Buffer Object. Surface switches are generally cheap.
	};

	bool CreateSurface(CIwTexture* pTexture, uint32_t width, uint32_t height, uint32_t usage);
	bool RecreateSurface(uint32_t width, uint32_t height);
	void MakeCurrent();

	static void MakeDisplayCurrent();
	//const CIwSVec2& GetClientUVExtent();
	const CIwFVec2& GetClientUVExtentFloat();
	uint32_t GetWidth();
	uint32_t GetHeight();
	uint32_t GetClientWidth();
	uint32_t GetClientHeight();
	bool HasAlphaChannel();

	bool IsValid()
	{
		return m_State != UNCREATED;
	}

	CIwTexture* GetTexture()
	{
		return m_pAttachedTexture;
	}

	CIwTexture* GetDepthTexture()
	{
		return m_pAttachedDepthTexture;
	}

	CIwGxSurfaceImplementation GetImplementation();

	const s3eSurfaceInfo& GetSurfaceInfo();

	//Private API
	void BindSurface();
	void ReleaseSurface();
	bool _HasAlphaInSurface()
	{
		return (m_Flags & HAS_ALPHA_IN_SURFACE_F) != 0;
	}
	void DestroySurface();
	uint32_t _GetFlags() { return m_Flags; }

private:
	// Internal state flags (must not overlap with creation flags)
	enum
	{
		OWNED_TEXTURE_F = (1 << 16), //!< Owns the associated texture
		HAS_ALPHA_IN_SURFACE_F = (1 << 17), //!< Actual surface has alpha
		CLIENT_WINDOW_F = (1 << 18), //!< Has a client window set
	};

	CIwTexture* m_pAttachedTexture;
	CIwTexture* m_pAttachedDepthTexture;

	enum SurfaceState
	{
		UNCREATED = 0,    //!< Default state
		CREATED = 1,    //!< has been created
		BOUND = 2,    //!< has been bound to the texture
		ACTIVE = 4,    //!< is the current surface
	};
	SurfaceState m_State;
	uint32_t m_Flags;

	// SW surface
	//CIwTexturePage* m_TPage;

	// HW surface
	CIwGxSurfaceImplementation m_HWImpl;

	s3eSurfaceInfo  m_HW_SurfaceInfo;

	//CIwSVec2        m_HW_ClientWindow; //propotion of the texture in the client window
	CIwFVec2        m_F_ClientWindow;  //propotion of the texture in the client window (float)

	SDL_Surface* m_surface;
									   // GLES1.x surface
	//EGLContext      m_EGLContext;
	//EGLSurface      m_EGLSurface;
	//EGLConfig       m_EGLConfig;

	// FBO surface
	//GLuint          m_Fbo;
	//GLuint          m_DepthTex;

};
