#include "../include/s3eConfig.h"

s3eConfigError s3eConfigGetError()
{
	return s3eConfigError();
}

const char * s3eConfigGetErrorString()
{
	return nullptr;
}

s3eResult s3eConfigGetString(const char * group, const char * name, char * value)
{
	return s3eResult();
}

s3eResult s3eConfigGetStringHash(uint32_t hash, char * value)
{
	return s3eResult();
}

s3eResult s3eConfigGetInt(const char * group, const char * name, int * value)
{
	return s3eResult();
}

s3eResult s3eConfigGetIntHash(uint32_t hash, int * value)
{
	return s3eResult();
}
