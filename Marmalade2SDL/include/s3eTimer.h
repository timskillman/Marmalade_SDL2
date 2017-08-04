#pragma once

#include "SRGXTypes.h"

/**
* @addtogroup s3egroup
* @{
*/

/**
* @defgroup timerapigroup S3E Timer API Reference
*
* For more information on the Timer functionality provided by the S3E module,
* see the "S3E Timer Overview" section of the <em>S3E API Documentation</em>.
*
* @supported{
*             @platform{Android,android}
*             @platform{iOS,ios}
*             @platform{Mac OS X,mac}
*             @platform{Mac OS X Simulator,macsim}
*             @platform{Tizen,tizen}
*             @platform{Windows Desktop,windows}
*             @platform{Windows Desktop Simulator,windowssim}
*             @platform{Windows Phone 8,wp8}
*             @platform{Windows Phone 8.1,wp81}
*             @platform{Windows Store 8,ws8}
*             @platform{Windows Store 8.1,ws81}
*             @platform{Windows 10,win10}
*             @platform{NaCl,nacl}
* }
*
* @{
*/

/**
* Timer Properties.
* @par Required Header Files
* s3eTimer.h
*/
typedef enum s3eTimerProperty
{
	S3E_TIMER_RESOLUTION    //!< [Read, int] Timer resolution, in milliseconds.
} s3eTimerProperty;

/**
* Timer Errors.
* @see s3eTimerGetError
* @see s3eTimerGetErrorString
* @par Required Header Files:
* s3eTimer.h
*/
typedef enum s3eTimerError
{
	S3E_TIMER_ERR_NONE = 0,    ///< No error.
	S3E_TIMER_ERR_PARAM = 1,    ///< Invalid parameter.
	S3E_TIMER_ERR_TOO_MANY = 2,    ///< Maximum number of timers (32) or callbacks exceeded .
	S3E_TIMER_ERR_ALREADY_REG = 3,    ///< The specified callback is already registered.
	S3E_TIMER_ERR_NOT_FOUND = 4,    ///< The specified timer or callback was not found for removal.
	S3E_TIMER_ERR_UNAVAIL = 5     ///< The timer subdevice is unavailable or disabled
} s3eTimerError;

/**
* Retrieves the last error, if any, for this subdevice.
* @see s3eTimerGetErrorString
*
* @remark Calling this function will retrieve the last error and then remove it
* from memory; therefore, any further calls to this function will not return
* an error unless a subsequent error has occurred.
*
* @par Required Header Files:
* s3eTimer.h
*/
s3eTimerError s3eTimerGetError();

/**
* Retrieves the last error as a string, if any, for this subdevice. This is only available in debug builds.
* @see s3eTimerGetError
*
* @remark This function, as opposed to s3eTimerGetError(), will always return
* the last error no matter how many times it is called. This function should not be
* relied upon to indicate whether an error has just occurred.
*
* @par Required Header Files:
* s3eTimer.h
*/
const char* s3eTimerGetErrorString();

/**
* Retrieves an integer property for this subdevice.
* @param property property to get.
* @return
* - The value of the requested property if property is valid.
* - -1 otherwise.\n
*         Call @ref s3eTimerGetError() to retrieve an error code.
*         This will return:
*   - @ref S3E_TIMER_ERR_PARAM if @e property is not valid.
* @remark
* This can be used to read the timer resolution via @ref S3E_TIMER_RESOLUTION.
* @par Required Header Files:
* s3eTimer.h
*/
int32_t s3eTimerGetInt(s3eTimerProperty property);

/**
* Return the uninterrupted system time.  This is a monotonic system clock that
* represents time since the S3E runtime started, measured in milliseconds.
* This clock is unaffected by changes to the devices wallclock time, or
* timezone.
* @return the time, measured in milliseconds since S3E startup.
* @remark This timer is accurate to at least 1/64 second (about 15ms) on all
* devices, so is useful for performing timing measurements.
* On some platforms the time returned by this function will be accurate to
* 1ms, but this is not guaranteed.
* Use s3eTimerGetInt(S3E_TIMER_RESOLUTION) to obtain the timer accuracy.
*/
int64_t s3eTimerGetUST();

inline uint64_t s3eTimerGetMs()
{
	return s3eTimerGetUST();
}

/**
* Similar to s3eTimerGetUST() but the returned time is in nanoseconds
* rather than milliseconds.  This function is only available of certain
* platforms that support sub-millisecond timing.  On all other platforms
* this function will return -1.  WARNING: This function can wrap around
* to zero before getting to INT64_MAX.  On iPhone for example this is
* implemented in terms mach_absolute_time which on some devices wraps every
* 50 minutes or so.
*/
int64_t s3eTimerGetUSTNanoseconds();

/**
* An alias for s3eTimerGetUST
*/
uint64_t s3eTimerGetMs();

/**
* Returns the time since the Epoch (00:00:00 UTC, January 1, 1970), measured
* in milliseconds.
*/
int64_t s3eTimerGetUTC();

/**
* Returns the offset from UTC of the current timezone, measured in
* milliseconds.
* @param when can be used to get the timezone offset at a particular
* time.  This is specified in milliseconds since the Epoc.  Passing
* NULL here will yield the timezone offset at the current time.
*/
int64_t s3eTimerGetLocaltimeOffset(int64_t* when);

/**
* Sets a timer.
* @param ms Time in milliseconds until timer is activated.
* @param fn Callback function to call when timer is activated.
* @param userData User specified data that will be passed to the
* userData parameter of the callback.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call @ref s3eTimerGetError() to retrieve an error code.
*         This will return one of:
*   - @ref S3E_TIMER_ERR_PARAM if @e fn is NULL.
*   - @ref S3E_TIMER_ERR_TOO_MANY if the maximum number of timers(32) has been exceeded.
*
* @remark The callback function @e fn will be called at least @e ms after the present time.
* The @e systemData parameter in the call to @e fn will be NULL and the @e userData
* parameter to @e fn will be set to the @e userData in the call to s3eTimerSetTimer().
*
* @remark Timers are only activated on calls to @ref s3eDeviceYield(), and they can interrupt a
* long yield period.
*
* @remark Timers only activate once - to implement a repeating timer additional calls to
* @ref s3eTimerSetTimer must be made.
*
* @remark Timer are identified by (@e fn, @e userData). If s3eTimerSetTimer is called more
* than once with the same (@e fn, @e userData) the previous timer will be replaced.
* Up to 32 timers may be registered at any one time.
* @par Required Header Files:
* s3eTimer.h
*/
s3eResult s3eTimerSetTimer(uint32_t ms, s3eCallback fn, void* userData);

/**
* Cancels a timer that was previously registered with
* @ref s3eTimerSetTimer().
* @param fn Callback function that was passed to s3eTimerSetTimer().
* @param userData userData that was passed to s3eTimerSetTimer().
* @return
*  - @ref S3E_RESULT_SUCCESS if no error occurred.
*  - @ref S3E_RESULT_ERROR if the operation failed.\n
*    Call @ref s3eTimerGetError() to retrieve an error code.
*    This will return one of:\n
*    - @ref S3E_TIMER_ERR_PARAM if @e fn is NULL.
*    - @ref S3E_TIMER_ERR_NOT_FOUND if (@e fn, @e userData)\n
*      is not in the list of active timers.
* @remark Timers are uniquely identified by (@e fn, @e userData) so
* both the @e fn and @e userData passed to @ref s3eTimerSetTimer()
* must be passed to @ref s3eTimerCancelTimer().
* @par Required Header Files:
* s3eTimer.h
*/
s3eResult s3eTimerCancelTimer(s3eCallback fn, void* userData);

/** @} */
/** @} */
