#pragma once
#include <stdint.h>
#include <SDL_rect.h>

typedef enum s3eResult
{
	S3E_RESULT_SUCCESS = 0,
	S3E_RESULT_ERROR = 1
}

typedef wchar_t s3eWChar;

typedef uint8_t s3eBool;

typedef int32_t(*s3eCallback) (void* systemData, void* userData);

