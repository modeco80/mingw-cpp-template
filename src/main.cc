#include <Common.hpp>


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR CmdLine, int cmdShow) { 
#ifdef DEVELOPMENT
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	
	HANDLE hConIn, hConOut;
	hConIn = CreateFile("CONIN$", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	hConOut = CreateFile("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	
	if(hConIn != INVALID_HANDLE_VALUE && hConOut != INVALID_HANDLE_VALUE) {
		SetStdHandle(STD_INPUT_HANDLE, hConIn);
		SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
		SetStdHandle(STD_ERROR_HANDLE, hConOut);
		
		// Allow VT commands
		DWORD dwOldMode = 0;
		if(GetConsoleMode(hConOut, &dwOldMode) != 0) {
			SetConsoleMode(hConOut, dwOldMode | 0x0200 /* ENABLE_VIRTUAL_TERMINAL_INPUT */);
		}
	}
	SetConsoleTitle("Debug Window");
#endif
	// Your code here. :)

	DEBUGLOG("This is a test message. Don't mind me.")
	DEBUGLOG("test multiple messages")
	
	while(1) Sleep(16);
	return 0;
}
