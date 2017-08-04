#pragma once

#include "s3eTimer.h"
#include "s3e.h"
#include "SDL_timer.h"
#include <time.h>

s3eTimerError s3eTimerGetError()
{
	return S3E_TIMER_ERR_NONE;
}

const char* s3eTimerGetErrorString()
{
	return "";
}

int32_t s3eTimerGetInt(s3eTimerProperty property)
{
	return 0;
}

int64_t s3eTimerGetUST()
{
	return SDL_GetTicks();
}

int64_t s3eTimerGetUSTNanoseconds()
{
	return -1;
}

int64_t s3eTimerGetUTC()
{
	return time(0);
}

int64_t s3eTimerGetLocaltimeOffset(int64_t* when)
{
	return 0;
}

s3eResult s3eTimerSetTimer(uint32_t ms, s3eCallback fn, void * userData)
{
	if (SDL_AddTimer(ms, (SDL_TimerCallback)fn, userData))
	{
		return S3E_RESULT_SUCCESS;
	}
	else
	{
		const char* error = SDL_GetError();
		return S3E_RESULT_ERROR;
	}
}

s3eResult s3eTimerCancelTimer(s3eCallback fn, void * userData)
{
	return s3eResult();
}
