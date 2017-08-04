#include "s3e.h"



	bool s3eDeviceCheckQuitRequest()
	{
		//return s3eVars::Gxwindow->hasquit();
		return false;
	}

	void s3eKeyboardUpdate()
	{

	}

	void s3ePointerUpdate()
	{

	}

	int s3ePointerGetTouchX(int i)
	{
		//return s3eVars::Gxwindow->mousex;
		return 0;
	}

	int s3ePointerGetTouchY(int i)
	{
		//return s3eVars::Gxwindow->mousey;
		return 0;
	}

	bool s3ePointerGetTouchState(int i)
	{
		//return s3eVars::Gxwindow->mousedown;
		return 0;
	}

	int s3ePointerWheelChangedEvent()
	{
		int mw = 0; //s3eVars::Gxwindow->mousewheel;
		//s3eVars::Gxwindow->mousewheel = 0;
		return mw;
	}

	void s3eDeviceYield(int cycles)
	{
		//s3eVars::Gxwindow->event();
	}

	bool s3eFileCheckExists(const char * path)
	{
#ifdef __WINDOWS__
		//This will get the file attributes bitlist of the file
		DWORD fileAtt = GetFileAttributesA(path);

		//If an error occurred it will equal to INVALID_FILE_ATTRIBUTES
		if (fileAtt == INVALID_FILE_ATTRIBUTES)
			//So lets throw an exception when an error has occurred
			return false;
			//throw GetLastError();

		//If the path referers to a directory it should also not exists.
		return ((fileAtt & FILE_ATTRIBUTE_DIRECTORY) == 0);
#endif
		return false;
	}

uint64_t s3eTimerGetMS()
{
	//Returns an unsigned 32-bit value representing the number of milliseconds since the SDL library initialized. 
	return (uint64_t)SDL_GetTicks();
}

