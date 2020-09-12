#pragma once

#define UNKNOWN_OS 0
#define WIN64 1
#define WIN32 2
#define LINUX 3

#ifdef _WIN64
	#define OS WIN64
#elif _WIN32
	#define OS WIN32
#elif __linux__
	#define OS LINUX
#else
	#define OS UNKNOWN_OS
#endif
