#pragma once
#include <stdint.h>
#include <SDL_rect.h>

class CIwColour
{
public:
	CIwColour() : r(0), g(0), b(0), a(255) {}

	CIwColour(uint32_t c) {
		Set(c);
	}
	
	CIwColour(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	inline uint32_t Get() const
	{
#ifdef IW_ENDIAN_BIG
		return  ((uint32)r) |
			((uint32)g << 8) |
			((uint32)b << 16) |
			((uint32)a << 24);
#else
		return *(uint32_t*)this;
#endif
	}

	void Set(uint32_t abgr)
	{
#ifdef IW_ENDIAN_BIG
		r = (abgr) & 0xff;
		g = (abgr >> 8) & 0xff;
		b = (abgr >> 16) & 0xff;
		a = (abgr >> 24) & 0xff;
#else
		*(uint32_t*)this = abgr;
#endif
	}

	CIwColour operator= (uint32_t rgba)
	{
		Set(rgba);
		return *this;
	}

	bool operator == (const CIwColour& other) const
	{
		return *(uint32_t*)this == *(uint32_t*)&other;
	}

	bool operator != (const CIwColour& other) const
	{
		return *(uint32_t*)this != *(uint32_t*)&other;
	}

	// Members
#ifndef __GNUC__
	union {
		struct
		{
#endif
			uint8_t   r;  //!< 8-bit red component.
			uint8_t   g;  //!< 8-bit green component.
			uint8_t   b;  //!< 8-bit blue component.
			uint8_t   a;  //!< 8-bit alpha component.
#ifndef __GNUC__
		};
		uint8_t force_dword_align;
	};
#endif
};


struct SRRect : public SDL_Rect
{
	SRRect() {
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
	SRRect(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	SRRect(const SDL_Rect &rect) {
		x = rect.x;
		y = rect.y;
		w = rect.w;
		h = rect.h;
	}

	SRRect intersect(const SDL_Rect &rect) {
		SDL_Rect r;
		SDL_IntersectRect(this, &rect, &r);
		return r;
	}
};


struct SRPointInt : public SDL_Point
{
	SRPointInt() {
		x = 0;
		y = 0;
	}
};

typedef enum s3eResult
{
	S3E_RESULT_SUCCESS = 0,  //!< The operation completed successfully
	S3E_RESULT_ERROR = 1     //!< An error occurred during the operation
} s3eResult;

typedef wchar_t s3eWChar;

typedef uint8_t s3eBool;

#if defined _MSC_VER
#define S3E_INLINE __forceinline
#define INLINE_MEMBER __forceinline
#endif

#if _MSC_VER
#define VALUE_IN_REGS
#endif

typedef int32_t(*s3eCallback) (void* systemData, void* userData);

