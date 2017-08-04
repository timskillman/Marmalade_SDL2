#pragma once

/* Dummy s3e header to replace Marmalade s3e.h header types and classes
*/

#define __NOFONTOUTLINE

#include <stdint.h>
#include "SDL.h" //works out platform for us
#include "SDL_platform.h" //works out platform for us
#include <SDL_log.h>
#include "s3eKeyboard.h"
#include "s3eSurface.h"
#include "s3eConfig.h"

#ifdef __IPHONEOS__
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif /* __IPHONEOS__ */

#ifdef __ANDROID__
#include <SDL_opengles.h>
#endif /* __ANDROID__ */

#ifdef __APPLE__
#include <TargetConditionals.h>
#ifdef TARGET_OS_MAC
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#endif
#endif

#ifdef __WINDOWS__
#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/glu.h>
#endif /* __WINDOWS__ */

#if defined (__WIN32__)
#include <Windows.h>
#endif // __WINDOWS__

// Defines
#define IW_GEOM_POINT   12
#define IW_GEOM_QPOINT  30
#define IW_GEOM_QPOINT_TO_GEOM_POINT (IW_GEOM_QPOINT - IW_GEOM_POINT)
#define PI 3.141592653589793f
#define IW_GEOM_ONE     (1 << IW_GEOM_POINT)
#define IW_GEOM_HALF    (1 << (IW_GEOM_POINT - 1))
#define IW_GEOM_ONE2    (1 << (IW_GEOM_POINT << 1))
#define IW_GEOM_QONE    (1 << IW_GEOM_QPOINT)
#define IW_GEOM_QHALF   (1 << (IW_GEOM_QPOINT - 1))
#define IW_GEOM_QONE2   ((int64)1 << (IW_GEOM_QPOINT << 1))
#define IW_GEOM_QEPSILON 0x200000
#define IW_ANGLE_PI     ((iwangle)IW_GEOM_HALF)
#define IW_ANGLE_2PI    ((iwangle)IW_GEOM_ONE)
#define IW_ANGLE_Q2PI   ((iwangle)IW_GEOM_QONE)

#define IW_GEOM_COS (iwfixed)std::cosf
#define IW_GEOM_SIN (iwfixed)std::sinf
#define IW_GEOM_QCOS IwGeomQCos
#define IW_GEOM_QSIN IwGeomQSin
#define IW_GEOM_ATAN2 IwGeomAtan2
#define IW_GEOM_TAN IwGeomTan
#define IW_GEOM_ACOS IwGeomACos
#define IW_GEOM_ASIN IwGeomASin
#define IW_GEOM_QACOS IwGeomQACos
#define IW_GEOM_QASIN IwGeomQASin
#define IW_GEOM_QATAN2 IwGeomQATan2

// Types

typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;

typedef int32  iwfixed;

typedef uint32_t iwufixed;
typedef int16_t  iwsfixed;
typedef uint16_t  iwusfixed;
typedef int32_t  iwqfixed;
typedef int32_t  iwangle;
typedef int32_t iwqangle;
typedef uint64_t uint64;
typedef int64_t int64;

#define IW_FIXED(x)     ((iwfixed)((x) * IW_GEOM_ONE))
#define IW_UFIXED(x)    ((iwufixed)((x) * IW_GEOM_ONE))
#define IW_SFIXED(x)    ((iwsfixed)((x) * IW_GEOM_ONE))

inline iwsfixed IW_SFIXED_FROM_FIXED(iwfixed a)
{
	//IwAssertMsgN(349, GEOM, a >> 31 == a >> 15, ("Conversion overflow"));
	return (iwsfixed)a;
}

#define IW_USFIXED(x)   ((iwusfixed)((x) * IW_GEOM_ONE))
#define IW_QFIXED(x)    ((iwqfixed)((x) * IW_GEOM_QONE))
#define IW_GEOM_ROUND(a) (((a) + IW_GEOM_HALF) >> IW_GEOM_POINT)
#define IW_FIXED_TO_FLOAT(a) ((float)(a) / (float)IW_GEOM_ONE)
inline iwfixed IW_FIXED_FROM_FLOAT(float a) { return (iwfixed)(a * (float)IW_GEOM_ONE); }

#define IW_SFIXED_FROM_FLOAT(a) IW_SFIXED_FROM_FIXED(IW_FIXED_FROM_FLOAT(a))

#define IW_ANGLE_FROM_DEGREES(x) ((iwangle)(((x) * IW_ANGLE_2PI) / 360.0))
#define IW_ANGLE_TO_DEGREES(x) ((int32)(((x) * 360 + (IW_ANGLE_2PI>>1)) / IW_ANGLE_2PI))

///// Functions

namespace s3eVars {
	static void* Gxcontext;
	extern void* Gxwindow;
}


enum s3eSurfaceProperty {
	S3E_SURFACE_WIDTH,
	S3E_SURFACE_HEIGHT,
	S3E_SURFACE_PITCH,
	S3E_SURFACE_PIXEL_TYPE,
	S3E_SURFACE_DEVICE_WIDTH,
	S3E_SURFACE_DEVICE_HEIGHT,
	S3E_SURFACE_DEVICE_PIXEL_TYPE,
	S3E_SURFACE_DEVICE_PITCH,
	S3E_SURFACE_BLIT_DIRECTION,
	S3E_SURFACE_DISPLAY,
	S3E_SURFACE_NUM_DISPLAYS,
	S3E_SURFACE_DEVICE_BLIT_DIRECTION,
	S3E_SURFACE_DEVICE_WIDTH_QUANTISED,
	S3E_SURFACE_DEVICE_HEIGHT_QUANTISED,
	S3E_SURFACE_DEVICE_ORIENTATION_LOCK,
	S3E_SURFACE_GL_MODE,
	S3E_SURFACE_WIDTH_UNSCALED,
	S3E_SURFACE_HEIGHT_UNSCALED,
	S3E_SURFACE_UI_SCALE
};

//int SurfaceGetInt(s3eSurfaceProperty v);
bool s3eDeviceCheckQuitRequest();
void s3eKeyboardUpdate();
void s3ePointerUpdate();
void s3eDeviceYield(int cycles);
int s3ePointerGetTouchX(int i);
int s3ePointerGetTouchY(int i);
int s3ePointerWheelChangedEvent();
bool s3ePointerGetTouchState(int i);
bool s3eFileCheckExists(const char * path);
int32_t s3eKeyboardGetState(s3eKey key);
uint64_t s3eTimerGetMS();


#define s3eDebugTracePrintf SDL_Log
