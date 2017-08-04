#pragma once
#include "SRGXTypes.h"

typedef struct s3eFile {

};

typedef struct s3eFileList s3eFileList;

typedef enum s3eFileSeekOrigin
{
	S3E_FILESEEK_SET = 0,   ///< Beginning of file.
	S3E_FILESEEK_CUR = 1,   ///< Current position of file pointer.
	S3E_FILESEEK_END = 2    ///< End of file.
} s3eFileSeekOrigin;

typedef enum s3eFileProperty
{
	/**
	* Returns wether the rom:// drive is valid and in use.
	* This is a useful indicator for telling if the data directory
	* has been mounted as RAM (ROM drive does not exist) or ROM (ROM drive does
	* exist).
	*/
	S3E_FILE_ROM_EXISTS = 1,

	/**
	* Return the total number of bytes of the storage available on the ram://
	* drive
	*/
	S3E_FILE_BYTES_TOTAL = 2,

	/**
	* Return the number of bytes free on ram:// drive
	*/
	S3E_FILE_BYTES_FREE = 3
} s3eFileProperty;

typedef enum s3eFileStats
{
	/**
	* [int, read] Returns whether the file exists.
	* This property will evaluate to 1 on any file that s3eFileOpen() can
	* open, and will hence include files in any registered user filesystem.
	* This produces the same result as calling s3eFileCheckExists().
	* This property will evaluate to 0 otherwise.
	*/
	S3E_FILE_ISFILE = 0,

	/**
	* [int, read] Returns whether the directory exists.
	* This property will evaluate to 1 on valid directory paths. This does not
	* include directories in the user file system.
	* This property will evaluate to 0 otherwise.
	*/
	S3E_FILE_ISDIR = 1,

	/**
	* [int, read] Returns whether the file exists in the user file system.
	* This property will evaluate to 1 on any file that the user file system
	* can open. This property will evaluate to 0 otherwise.
	*/
	S3E_FILE_ISUSER = 2,

	/**
	* [int, read] Returns whether the file is writable.
	* This property will evaluate to 1 on any file that exists on a writable
	* drive.
	* This property will evaluate to 0 on any file that exists on a read-only
	* drive.
	* For files that exists on a ROM drive but are shadowable to RAM this will
	* return 1, as opening the file for writing would succeed.
	* This property will fail to evaluate for a file that does not exist
	* (return -1).
	*/
	S3E_FILE_ISWRITABLE = 3,

	/**
	* [int, read] Returns the size of the file, in bytes.
	* This property will fail to evaluate (return -1) on a non-existant file.
	*/
	S3E_FILE_SIZE = 4,

	/**
	* [int, read] Returns the date of last modification of the file, in
	* milliseconds elapsed since midnight (00:00:00), January 1, 1970.
	* This is the same time datum as used by the Timer module. The date
	* returned is in the local time of the device.
	* Querying this property will fail for files in the the user file system.
	* This property will fail to evaluate (return -1) on a non-existant file.
	*/
	S3E_FILE_MODIFIED_DATE = 5,

	/**
	* [int, read] Returns the free space in bytes on the drive that stores
	* this file.
	* The path specified must be a valid directory on the drive, for
	* example '/' or 'ram://'.
	* If querying the free space fails for any reason (invalid drive, invalid
	* path), the return value of s3eFileGetFileInt() will always be 0.
	* If S3E_FILE_DRIVE_BYTES_FREE == S3E_FILE_DRIVE_BYTES_TOTAL then the drive
	* is empty. If S3E_FILE_DRIVE_BYTES_FREE == 0 then the drive is full.
	*/
	S3E_FILE_DRIVE_BYTES_FREE = 6,

	/**
	* [string, read] Returns a string containing the drive on which the file
	* is stored.
	* If the file does not exist this property will fail to evaluate (return
	* NULL string). If the file is on the user file system, this will return
	* "user" (without the '://' drive syntax)
	*/
	S3E_FILE_DRIVE = 7,

	/**
	* [int, read] Returns the total size in bytes of the drive that contains
	* this path. The path specified must be a valid directory on the drive, for
	* example '/' or 'ram://'.  If querying the total size fails for any reason
	* (invalid drive, invalid path), the return value of s3eFileGetFileInt()
	* will always be 0.
	*/
	S3E_FILE_DRIVE_BYTES_TOTAL = 8,

	/**
	* [int, read] Returns a real path string to the file for the drive or path
	* specified.  For example 'rom://myfile.png' could return
	* 'g:/data/myfile.png'
	*/
	S3E_FILE_REAL_PATH = 9,
} s3eFileStats;

int32_t s3eFileGetInt(s3eFileProperty property);

int64_t s3eFileGetFileInt(const char* filename, s3eFileStats stat);

char* s3eFileGetFileString(const char* filename, s3eFileStats stat, char* str, int len);

typedef enum s3eFileError
{
	S3E_FILE_ERR_NONE = 0,     ///< No Error.
	S3E_FILE_ERR_PARAM = 1,     ///< Invalid parameter.
	S3E_FILE_ERR_TOO_MANY = 2,     ///< Maximum number of callbacks exceeded.
	S3E_FILE_ERR_ALREADY_REG = 3,     ///< The specified callback is already registered.
	S3E_FILE_ERR_NOT_FOUND = 4,     ///< Path not found / callback not found for removal.
	S3E_FILE_ERR_UNAVAIL = 5,     ///< file support is unavailable or feature is not supported.
	S3E_FILE_ERR_DEVICE = 6,     ///< The underlying file device failed.
	S3E_FILE_ERR_UNSUPPORTED = 7,     ///< The action requested was is not supported.
	S3E_FILE_ERR_MEM = 8,     ///< Out of operating system memory during operation.
	S3E_FILE_ERR_GENERIC = 9,     ///< Unspecified error.
	S3E_FILE_ERR_INVALID_DRIVE = 10,   ///< Invalid/unsupported drive specified in path. This error code is no longer used.
	S3E_FILE_ERR_INVALID_PATH = 11,   ///< The path could not be resolved onto the device filesytem (e.g. opening ROM://../file).
	S3E_FILE_ERR_DATA = 12,   ///< Data read/write error.

	S3E_FILE_ERR_INVALID_MODE = 1000,  ///< Invalid mode specification for s3eFileOpen().
	S3E_FILE_ERR_EXISTS = 1001,  ///< File/Path already exists.
	S3E_FILE_ERR_NOT_EMPTY = 1002,  ///< Directory not empty on removal.
	S3E_FILE_ERR_ACCESS = 1003,  ///< Access permission/error deleting file.
	S3E_FILE_ERR_NO_MORE = 1004,  ///< No more files in directory listing.
	S3E_FILE_ERR_EOF = 1005   ///< EOF reached during file operation.
} s3eFileError;


s3eFileError s3eFileGetError();
const char* s3eFileGetErrorString();
s3eFile* s3eFileOpen(const char* filename, const char* mode); //
s3eFile* s3eFileOpenFromMemory(void* buffer, size_t bufferLen);
s3eResult s3eFileClose(s3eFile* file); //
s3eResult s3eFileFlush(s3eFile* file);
size_t s3eFileRead(void* buffer, size_t elemSize, size_t noElems, s3eFile* file); //
size_t s3eFileWrite(const void* buffer, size_t elemSize, size_t noElems, s3eFile* file); //
int32_t s3eFileGetChar(s3eFile* file);
int32_t s3eFilePutChar(char c, s3eFile* file);
char* s3eFileReadString(char* string, uint32_t maxLen, s3eFile* file);
bool s3eFileEOF(s3eFile* file);
s3eResult s3eFileSeek(s3eFile* file, long int offset, s3eFileSeekOrigin origin);
long int s3eFileTell(s3eFile* file);
int32_t s3eFileGetSize(s3eFile* file);
s3eResult s3eFileMakeDirectory(const char* dirName);
s3eResult s3eFileDeleteDirectory(const char* dirName);
bool s3eFileCheckExists(const char* filename);
s3eResult s3eFileRename(const char* src, const char* dest);
s3eResult s3eFileDelete(const char* filename);
s3eResult s3eFileTruncate(const char* filename, size_t length);
uint64_t s3eFileGetLastWriteTime(const char* filename);
s3eFileList* s3eFileListDirectory(const char* dirName);
s3eResult s3eFileListNext(s3eFileList* handle, char* filename, int filenameLen);
s3eResult s3eFileListClose(s3eFileList* handle);

