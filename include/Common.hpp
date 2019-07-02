#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef DEBUG
#define DEVELOPMENT
#endif


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


namespace {

	#ifdef DEVELOPMENT
	inline void DebugLog(const char* file, int line, const char* format, ...) {
		va_list val;
		char* formatted = (char*)calloc(65535, sizeof(char));
        char* final_str = (char*)calloc(65535, sizeof(char));
		
		// format the message buffer
		va_start(val, format);
		vsnprintf(formatted, 65509, format, val);
		va_end(val);
		
		// format the final string buffer
		snprintf(final_str, 512, "*** Debug (%s:%d): %s ***\n", file, line, formatted);
		free((char*) formatted);
		
		// TODO: We should possibly also log to a file.
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), (void*)final_str, strlen(final_str), NULL, NULL);
		free((char*) final_str);
	}
	#define DEBUGLOG(format, ...) DebugLog(__FILE__, __LINE__, format, ##__VA_ARGS__);
	#else
	#define DEBUGLOG(format, ...)
	#endif

}
