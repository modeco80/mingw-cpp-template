#include <Common.hpp>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR CmdLine, int cmdShow) { 
#ifdef DEVELOPMENT
	// since this will be compiled as a Windows application,
	// we manually re-allocate the console to show debugging messages.
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CONOUT$", "w", stdout);
	SetConsoleTitle("Debug Window");
#endif
	// Your code here. :)

	DEBUGLOG("This is a test message. Don't mind me.")
	
	while(1) Sleep(16);
	return 0;
}
