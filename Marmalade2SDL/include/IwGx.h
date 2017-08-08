#pragma once

#include <SDL.h>
#include <SDL_image.h>

#ifdef __IPHONEOS__
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif /* __IPHONEOS__ */

#ifdef __ANDROID__
#include <SDL_opengles.h>
#endif /* __ANDROID__ */

#ifdef __WINDOWS__
#include <GL/gl.h>
#include <windows.h>
#include "SDL_syswm.h"
#endif /* __WINDOWS__ */

#include "s3eTypes.h"
#include "CIwVector.h"
#include "IwMaterial.h"
#include "SDLwindow.h"
#include "SDLtexture.h"
#include "IwDebug.h"

#define IW_MAX_VERTS 30000
#define IW_MAX_INDICES 10000
#define IW_MAX_LINDEX 10000
#define IW_MAX_UVS 20000
#define IW_NEARZ 1.0f  //IW_NEARZ and IW_FARZ *MUST* be positive values used only for perspective projection
#define IW_FARZ 1500.0f

#define IW_2D_DIST -0.9f	//2D fill rectangle distance
#define IW_2D_TDIST 0.0f	//2D text rendering distance (should be in front of rectangle distance)

#define PSPVALUE -800.f		//3D rendering depth
#define DP2D -100.f			//2D rendering depth in 3D context (used for Point3Dto2D, renderShapes.cpp)

typedef enum IwGxPrimType {
	IW_GX_LINE_NONE,
	IW_GX_LINE_LIST,
	IW_GX_LINE_NONE2,
	IW_GX_LINE_STRIP,
	IW_GX_TRI_LIST,
	IW_GX_TRI_STRIP,
	IW_GX_TRI_FAN,
	IW_GX_QUAD_LIST,
	IW_GX_QUAD_STRIP,
} IwGxPrimType;

typedef enum IwGxClearBufferFlags {
	IW_GX_DEPTH_BUFFER_F = GL_DEPTH_BUFFER_BIT,
	IW_GX_COLOUR_BUFFER_F = GL_COLOR_BUFFER_BIT
} IwGxClearBufferFlags;

typedef enum IwGxLightType
{
	IW_GX_LIGHT_AMBIENT,        //!< ambient light.
	IW_GX_LIGHT_DIFFUSE,        //!< diffuse light.
} IwGxLightType;


namespace SGVars {
	//Static vars
	extern SDLwindow* Gxwindow;
};


	//Marmalade quivalent Functions
	void InitVars();
	bool IwGxInit(SDLwindow* window);
	bool IwGxInit(const char * title = "SRGX", int width = 800, int height = 600, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	void IwGxTerminate();
	void IwGxSetPerspMul(float perspmul);
	void IwGxSetOrtho(float left, float right, float top, float bottom, float nearz = IW_NEARZ, float farz = IW_FARZ);
	void IwGxSetOrtho();
	void IwGxSetFarZNearZ(float farz, float nearz);
	void IwGxSetZDepthFixed(float z); //TODO
	void IwGxSetViewMatrix(CIwFMat* viewmat);
	void IwGxSetModelMatrix(CIwFMat* modelmat);
	CIwFMat IwGxGetModelViewClipMatrix();
	void IwGxSetLightType(uint32_t LightNo, uint32_t LightType);
	void IwGxSetLightDirn(uint32_t LightNo, CIwFVec3* direc);
	void IwGxSetLightPos(uint32_t LightNo, CIwFVec3* pos);
	void IwGxSetLightCol(uint32_t LightNo, CIwColour* colour);
	void IwGxSetFogCol(GLuint* colour);
	void IwGxSetFogFarZNearZ(float far, float near);
	void IwGxFogOn();
	void IwGxSetColClear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void IwGxClear(GLenum flags);
	void IwGxLightingOn();
	void IwGxLightingOff();
	void IwGxSetMaterial(CIwMaterial* material);
	void IwGxLightingSpecular(bool s); //TODO
	uint32_t IwGxGetScreenWidth();
	uint32_t IwGxGetScreenHeight();

	void IwGxFlush();
	void IwGxSwapBuffers();
	uint16_t IwGxClipVec(CIwFVec3 vec);

	void IwGxSetColStream(GLvoid* cols, int count = 0);
	void IwGxSetUVStream(GLvoid* uv);
	void IwGxSetNormStream(const GLvoid* normals, int count = 0);
	void IwGxSetNormStream(uint32_t p);
	void IwGxSetVertStreamModelSpace(const GLvoid* verts, int count);
	void IwGxSetVertStreamScreenSpace(const GLvoid* verts, int count);
	void IwGxSetVertStream(const GLvoid* verts, int count);
	void IwGxDrawPrims(uint16_t mode, GLvoid* indices, int indexNo);

	void _IwGxSetViewRect(GLint x, GLint y, GLsizei width, GLsizei height);

	//Non-Marmalade calls
	void DrawPolygon3D(CIwFVec3* verts, int32_t numberVerts, bool closed);
	void Perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar); //gluPerspective alternative
}
