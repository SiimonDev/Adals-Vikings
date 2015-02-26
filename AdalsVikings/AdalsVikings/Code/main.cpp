#include "Logics\Game.h"
////define the minimum operating system for the application:
//#define _win32_winnt _win32_winnt_winxp //windows xp
////get rid of the annoying min() and max() macros:
//#define nominmax
////include the windows header:
//#include <windows.h>
//
//
////now write the entry point.  it is the 21st century, so write unicode programs.  this is the unicode entry point.
//
//int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
//{
//	Game game;
//	game.run();
//
//	return 0;
//}

int main()
{
	Game game;
	game.run();

	return 0;
}