#pragma once

#include <SDL.h>
#include <string>
#include <sstream>
#include "SDL_syswm.h"

//SDL_Renderer* gRenderer = NULL;

class SDLwindow {
public:
	SDLwindow();

	bool init(const char * title, int width, int height, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	void setCaption(std::string caption);
	void destroy();
	void update();
	void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	int event();

	int getWidth();
	int getHeight();
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	void forceMouseUp();
	bool isMinimized();
	bool hasquit();
	std::string getSystemInfo();

#ifdef __WINDOWS__
	//windows specific functions
	HWND getHwnd();
	void createWindowsMenu();
#endif

	SDL_Window* handle() { return mWindow; }

	SDL_Renderer* graphics;
	SDL_Event ev;

	int mousex;
	int mousey;
	int mousewheel;
	bool mousedown;
	bool mousedrag;
	bool mouseup;
	bool wasDragging;

	//Window dimensions
	int mWidth;
	int mHeight;

private:
	SDL_Window* mWindow;
	SDL_GLContext* GLcontext;
	SDL_DisplayMode mode;


	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;

	bool quit;
};

