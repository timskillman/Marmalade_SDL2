#include "SDLwindow.h"

SDLwindow::SDLwindow() {
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
	mousex = 0;
	mousey = 0;
	mousedown = false;
	mousedrag = false;
	mouseup = false;
	wasDragging = false;
	quit = false;
}

bool SDLwindow::init(const char * title, int width, int height, Uint32 flags) {
	//Create window
	mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
	if (mWindow != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = width;
		mHeight = height;
		SDL_GetDesktopDisplayMode(0, &mode);
		graphics = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

#if __WINDOWS__
		createWindowsMenu();
#endif

	}
	else
	{
		SDL_Log("Window error %d", SDL_GetError());
	}



	return mWindow != NULL;
}

int SDLwindow::event()
{
	int p = SDL_PollEvent(&ev);
	if (p) {
		switch (ev.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEMOTION:
			mousex = ev.motion.x;
			mousey = ev.motion.y;
			wasDragging = false;
			mouseup = false;
			if (mousedown) mousedrag = true;
			break;
		case SDL_MOUSEWHEEL:
			mousewheel = ev.motion.x;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (ev.button.button) {
			case SDL_BUTTON_LEFT:
				if (!mousedown) {
					mousex = ev.button.x;
					mousey = ev.button.y;
					mousedown = true;
					mousedrag = false;
					mouseup = false;
					wasDragging = false;
				}
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (ev.button.button) {
			case SDL_BUTTON_LEFT:
				wasDragging = mousedrag;
				mousex = ev.button.x;
				mousey = ev.button.y;
				mousedown = false;
				mousedrag = false;
				mouseup = true;
				break;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (ev.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				//Get new dimensions and repaint on window size change
				mWidth = ev.window.data1;
				mHeight = ev.window.data2;
				break;

			case SDL_WINDOWEVENT_ENTER:
				mMouseFocus = true;
				break;

				//Mouse left window
			case SDL_WINDOWEVENT_LEAVE:
				mMouseFocus = false;
				break;

				//Window has keyboard focus
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				mKeyboardFocus = true;
				break;

				//Window lost keyboard focus
			case SDL_WINDOWEVENT_FOCUS_LOST:
				mKeyboardFocus = false;
				break;

				//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
				mMinimized = true;
				break;

				//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
				mMinimized = false;
				break;

				//Window restored
			case SDL_WINDOWEVENT_RESTORED:
				mMinimized = false;
				break;

			}
		}
	}
	return p;
}

void SDLwindow::destroy()
{
	SDL_DestroyRenderer(graphics);

	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

void SDLwindow::update()
{
	SDL_RenderPresent(graphics);
}

void SDLwindow::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(graphics, r,g,b,a);
	SDL_RenderClear(graphics);
}

int SDLwindow::getWidth()
{
	return mWidth;
}

int SDLwindow::getHeight()
{
	return mHeight;
}

bool SDLwindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool SDLwindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

void SDLwindow::forceMouseUp()
{
	mousedown = false;
	mousedrag = false;
}

bool SDLwindow::isMinimized()
{
	return mMinimized;
}

bool SDLwindow::hasquit()
{
	return quit;
}

void SDLwindow::setCaption(std::string caption)
{
	SDL_SetWindowTitle(mWindow, caption.c_str());
}

std::string SDLwindow::getSystemInfo()
{
	//Must be called after the creation of the SDL_window

	SDL_SysWMinfo info;
	std::string subsystem = "Unknown";

	SDL_VERSION(&info.version); /* initialize info structure with SDL version info */

	if (SDL_GetWindowWMInfo(mWindow, &info)) { /* the call returns true on success */
											  /* success */
		switch (info.subsystem) {
		case SDL_SYSWM_UNKNOWN:   break;
		case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows(TM)";  break;
		case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
#if SDL_VERSION_ATLEAST(2, 0, 3)
		case SDL_SYSWM_WINRT:     subsystem = "WinRT";                  break;
#endif
		case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
		case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
		case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
#if SDL_VERSION_ATLEAST(2, 0, 2)
		case SDL_SYSWM_WAYLAND:   subsystem = "Wayland";                break;
		case SDL_SYSWM_MIR:       subsystem = "Mir";                    break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 4)
		case SDL_SYSWM_ANDROID:   subsystem = "Android";                break;
#endif
#if SDL_VERSION_ATLEAST(2, 0, 5)
		case SDL_SYSWM_VIVANTE:   subsystem = "Vivante";                break;
#endif
		}

		SDL_Log("This program is running SDL version %d.%d.%d on %s",
			(int)info.version.major,
			(int)info.version.minor,
			(int)info.version.patch,
			subsystem.c_str());
	}
	else {
		/* call failed */
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't get window information: %s", SDL_GetError());
	}

	return subsystem;
}

#ifdef __WINDOWS__
//windows specific functions
HWND SDLwindow::getHwnd()
{
	struct SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(mWindow, &info);
	HWND hwnd = info.info.win.window;
	return hwnd;
}

void SDLwindow::createWindowsMenu()
{
	HWND myWindow;
	HMENU myMenu;

	myWindow = getHwnd();
	SDL_Log("HWND = %d", myWindow);
	myMenu = LoadMenu(NULL, MAKEINTRESOURCE(102));
	SetMenu(myWindow, myMenu);
}

#endif

