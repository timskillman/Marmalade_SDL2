#include "s3eSurface.h"
#include "IwGx.h"

void s3eSurfaceClear(uint8_t r, uint8_t g, uint8_t b)
{
}

void s3eSurfaceBlank(uint8_t bitpattern)
{
}

int s3eSurfaceGetInt(s3eSurfaceProperty var) {
	int v = 0;
	switch (var) {
	case s3eSurfaceProperty::S3E_SURFACE_WIDTH:
		return IwGxGetScreenWidth();
	case s3eSurfaceProperty::S3E_SURFACE_HEIGHT:
		return IwGxGetScreenHeight();
	}
	return v;
}

s3eResult s3eSurfaceSetInt(s3eSurfaceProperty property, int32_t val)
{
	return s3eResult();
}