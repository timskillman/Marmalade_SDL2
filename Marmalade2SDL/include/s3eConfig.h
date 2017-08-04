/*
* (C) 2001-2012 Marmalade. All Rights Reserved.
*
* This document is protected by copyright, and contains information
* proprietary to Marmalade.
*
* This file consists of source code released by Marmalade under
* the terms of the accompanying End User License Agreement (EULA).
* Please do not use this program/source code before you have read the
* EULA and have agreed to be bound by its terms.
*/
#ifndef S3E_CONFIG_H
#define S3E_CONFIG_H

#include "SRGXTypes.h"

/**
* @addtogroup s3egroup
* @{
*/

/**
* @defgroup configapigroup S3E Configuration API Reference
*
* For more information on the Configuration functionality provided by the S3E module,
* see the "S3E Configuration Overview" section of the <em>S3E API Documentation</em>.
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
* @{
*/

/**
* Config Errors.
* @see s3eConfigGetError
* @see s3eConfigGetErrorString
* @par Required Header Files
* s3eConfig.h
*/
typedef enum s3eConfigError
{
	S3E_CONFIG_ERR_NONE = 0, ///< No Error
	S3E_CONFIG_ERR_PARAM = 1, ///< Invalid parameter.

	S3E_CONFIG_ERR_NOT_FOUND = 4, ///< Requested configuration value not found

	S3E_CONFIG_ERR_PARSE = 6  ///< Config value could not be parsed as an integer
} s3eConfigError;

/**
* The maximum length of a variable name or value used in s3eConfigGetInt or
* s3eConfigGetString, including the null terminator.
* Any names or values longer than this in the icf file will be truncated.
*/
#define S3E_CONFIG_STRING_MAX 1024

/**
* Retrieves the last error, if any, for this subdevice.
* @see s3eConfigGetErrorString
*
* @remark Calling this function will retrieve the last error and then remove
* it * from memory; therefore, any further calls to this function will not
* return * an error unless a subsequent error has occurred.
*
* @par Required Header Files
* s3eConfig.h
*/
s3eConfigError s3eConfigGetError();

/**
* Retrieves the last error as a string, if any, for this subdevice. This is
* only available in debug builds.
* @see s3eConfigGetError
*
* @remark This function, as opposed to s3eConfigGetError(), will always return
* the last error no matter how many times it is called. This function should not be
* relied upon to indicate whether an error has just occurred.
*
* @par Required Header Files
* s3eConfig.h
*/
const char* s3eConfigGetErrorString();

/**
* Gets a configuration setting as a string from the given group and name.
* @param group Group string name.
* @param name Variable string name.
* @param value Is set to the recovered configuration string.
* @result
* - @ref S3E_RESULT_SUCCESS if no error occurred
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call @ref s3eConfigGetError() to retrieve the error code.
*         This will return one of:
*   - @ref S3E_CONFIG_ERR_PARAM if any of @e group, @e name or @e value are NULL.
*   - @ref S3E_CONFIG_ERR_NOT_FOUND if the [@e group] @e name configuration setting was not found in the .icf files
* @remark @e value should be large enough to store the entire value. The
* maximum size of a value is @ref S3E_CONFIG_STRING_MAX (256) bytes
*
* @note If the string is not found or some error occurs, @e value is not changed.
*
* @see s3eConfigGetInt
* @par Required Header Files
* s3eConfig.h
*/
s3eResult s3eConfigGetString(const char* group, const char* name, char* value);

s3eResult s3eConfigGetStringHash(uint32_t hash, char* value);

/**
* Gets a configuration setting as an integer from the group/name.
* @param group Group string name.
* @param name Variable string name.
* @param value Stores configuration setting integer. The variable @a value is only modified if the setting is found.
* @result
* - @ref S3E_RESULT_SUCCESS if no error occurred
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call @ref s3eConfigGetError() to retrieve the error code.
*         This will return one of:
*   - @ref S3E_CONFIG_ERR_PARAM if any of @e group, @e name or @e value are NULL.
*   - @ref S3E_CONFIG_ERR_NOT_FOUND if the [@e group] @e name configuration setting was not found in the .icf files
*   - @ref S3E_CONFIG_ERR_PARSE if the string for this setting cannot be parsed as an integer
* @remark
* This function first reads the configuration value as a string, then attempts to interpret it as an integer.
* The strings 'true' and 'on' will be converted to integer value 1. The strings 'false' and 'off' will be
* converted to 0.
* A string of the form 0x\<number\>, e.g., 0x1000, will be parsed as a hexadecimal integer.
* Otherwise the string will be parsed as decimal integer.
*
* @note If the setting is not found or some error occurs, @a value is not changed.
* If the setting is found @a value is set to be the recovered integer or the integer as it has been interpreted.
*
* @see s3eConfigGetString
*/
s3eResult s3eConfigGetInt(const char* group, const char* name, int* value);

s3eResult s3eConfigGetIntHash(uint32_t hash, int* value);

#endif /* !S3E_CONFIG_H */

/** @} */
/** @} */
