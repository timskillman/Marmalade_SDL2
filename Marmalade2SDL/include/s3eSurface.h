#pragma once

#include "SRGXTypes.h"

#define S3E_SURFACE_PIXEL_SIZE_8        0x10
/** Pixel size is two bytes */
#define S3E_SURFACE_PIXEL_SIZE_16       0x20
/** Pixel size is three bytes */
#define S3E_SURFACE_PIXEL_SIZE_24       0x30
/** Pixel size is four bytes */
#define S3E_SURFACE_PIXEL_SIZE_32       0x40
// \cond HIDDEN_DEFINES
#define S3E_SURFACE_PIXEL_SIZE_MASK     0x70

#define S3E_SURFACE_PIXEL_ORDER_RGB     0x400
/**
* Pixel data is stored with the red colour component in the least significant
* bits, and blue in the most significant bits
*/
#define S3E_SURFACE_PIXEL_ORDER_BGR     0x800

/** Pixel data is 4 bits per colour, RRRRGGGGBBBB or BBBBGGGGRRRR */
#define S3E_SURFACE_PIXEL_TYPE_444      0x1
/** Pixel data is 5 bits red, 6 bits green, 5 bits blue, RRRRRGGGGGGBBBBB or BBBBBGGGGGGRRRRR */
#define S3E_SURFACE_PIXEL_TYPE_565      0x2
/** Pixel data is 5 bits per colour channel, RRRRRGGGGGBBBBB or BBBBBGGGGGRRRRR */
#define S3E_SURFACE_PIXEL_TYPE_555      0x3
/** Pixel data is 6 bits per colour channel, RRRRRRGGGGGGBBBBBB or BBBBBBGGGGGGRRRRRR */
#define S3E_SURFACE_PIXEL_TYPE_666      0x4
/** Pixel data is 8 bits per colour channel, RRRRRRRRGGGGGGGGBBBBBBBB or BBBBBBBBGGGGGGGGRRRRRRRR */
#define S3E_SURFACE_PIXEL_TYPE_888      0x5
/** Pixel data is 5 bits red, 5 bits green, 5 bits blue and 1 bit ignored, RRRRRGGGGGGBBBBBX or BBBBBGGGGGGRRRRRX */
#define S3E_SURFACE_PIXEL_TYPE_5551     0x6
/** Pixel data is 8 bits ignored, 8 bits red, 8 bits green, 8 bits blue */
#define S3E_SURFACE_PIXEL_TYPE_X888     0x7
// \cond HIDDEN_DEFINES
#define S3E_SURFACE_PIXEL_TYPE_MASK     0xf

typedef enum s3eSurfacePixelType
{
	S3E_SURFACE_PIXEL_TYPE_RGB444 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_444,
	S3E_SURFACE_PIXEL_TYPE_RGB555 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_555,
	S3E_SURFACE_PIXEL_TYPE_RGB5551 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_5551,
	S3E_SURFACE_PIXEL_TYPE_RGB565 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_565,
	S3E_SURFACE_PIXEL_TYPE_RGB666 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_666,
	S3E_SURFACE_PIXEL_TYPE_RGB888 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_888,
	S3E_SURFACE_PIXEL_TYPE_RGB888_3B = S3E_SURFACE_PIXEL_SIZE_24 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_888,
	S3E_SURFACE_PIXEL_TYPE_XRGB888 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_RGB | S3E_SURFACE_PIXEL_TYPE_X888,

	S3E_SURFACE_PIXEL_TYPE_BGR444 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_444,
	S3E_SURFACE_PIXEL_TYPE_BGR555 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_555,
	S3E_SURFACE_PIXEL_TYPE_BGR5551 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_5551,
	S3E_SURFACE_PIXEL_TYPE_BGR565 = S3E_SURFACE_PIXEL_SIZE_16 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_565,
	S3E_SURFACE_PIXEL_TYPE_BGR666 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_666,
	S3E_SURFACE_PIXEL_TYPE_BGR888 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_888,
	S3E_SURFACE_PIXEL_TYPE_BGR888_3B = S3E_SURFACE_PIXEL_SIZE_24 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_888,
	S3E_SURFACE_PIXEL_TYPE_XBGR888 = S3E_SURFACE_PIXEL_SIZE_32 | S3E_SURFACE_PIXEL_ORDER_BGR | S3E_SURFACE_PIXEL_TYPE_X888
} s3eSurfacePixelType;

typedef struct s3eSurfaceInfo
{
	/** Width of surface. */
	uint32_t              m_Width;
	/** Height of surface. */
	uint32_t              m_Height;
	/** Pitch of surface. */
	uint32_t              m_Pitch;
	/** Pixel type of surface. This can be any of those listed as part of s3eSurfacePixelType. */
	s3eSurfacePixelType m_PixelType;
	/** Pointer to surface data area. */
	void*               m_Data;
} s3eSurfaceInfo;

void s3eSurfaceClear(uint8_t r, uint8_t g, uint8_t b);

void s3eSurfaceBlank(uint8_t bitpattern);

typedef enum s3eSurfaceProperty
{
	S3E_SURFACE_WIDTH = 0,
	S3E_SURFACE_HEIGHT = 1,
	S3E_SURFACE_PITCH = 2,
	S3E_SURFACE_PIXEL_TYPE = 3,
	S3E_SURFACE_DEVICE_WIDTH = 4,
	S3E_SURFACE_DEVICE_HEIGHT = 5,
	S3E_SURFACE_DEVICE_PIXEL_TYPE = 6,
	S3E_SURFACE_DEVICE_PITCH = 7,
	S3E_SURFACE_BLIT_DIRECTION = 8,
	S3E_SURFACE_DISPLAY = 9,
	S3E_SURFACE_NUM_DISPLAYS = 10,
	S3E_SURFACE_DEVICE_BLIT_DIRECTION = 11,
	S3E_SURFACE_DEVICE_WIDTH_QUANTISED = 12,
	S3E_SURFACE_DEVICE_HEIGHT_QUANTISED = 13,
	S3E_SURFACE_DEVICE_ORIENTATION_LOCK = 14,
	S3E_SURFACE_GL_MODE = 15,
	S3E_SURFACE_WIDTH_UNSCALED = 16,
	S3E_SURFACE_HEIGHT_UNSCALED = 17,
	S3E_SURFACE_UI_SCALE = 18,
} s3eSurfaceProperty;

int s3eSurfaceGetInt(s3eSurfaceProperty property);

s3eResult s3eSurfaceSetInt(s3eSurfaceProperty property, int32_t val);

typedef enum s3eSurfaceBlitDirection
{
	/** No rotation. */
	S3E_SURFACE_BLIT_DIR_NORMAL = 0,

	/** 90 degrees clockwise rotation copying from source to destination. */
	S3E_SURFACE_BLIT_DIR_ROT90 = 1,

	/** 180 degrees rotation copying from source to destination. */
	S3E_SURFACE_BLIT_DIR_ROT180 = 2,

	/** 270 degrees clockwise rotation copying from source to destination. */
	S3E_SURFACE_BLIT_DIR_ROT270 = 3,

	/**
	* For use with s3eSurfaceSetup; This prevents any rotated copy occurring
	* during s3eSurfaceShow.
	*/
	S3E_SURFACE_BLIT_DIR_NATIVE = 4
} s3eSurfaceBlitDirection;

typedef struct s3eSurfaceOrientation
{
	bool                 m_OrientationChanged;  ///< True if orientation has changed
	uint32_t                  m_Width;               ///< New user surface width
	uint32_t                  m_Height;              ///< New user surface height
	s3eSurfaceBlitDirection m_DeviceBlitDirection; ///< New device blit direction
	uint32_t                  m_Pitch;               ///< New user surface pitch
} s3eSurfaceOrientation;


