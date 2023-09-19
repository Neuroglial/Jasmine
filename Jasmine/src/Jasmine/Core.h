#pragma once

#ifdef JASMINE_WINDOWS
#ifdef JASMINE_BUILD_DLL
	#define JASMINE_API _declspec(dllexport)
#else
	#define JASMINE_API _declspec(dllimport)
#endif // JASMINE_BUILD_DLL

#else
#error JASMINE_ONLY_SUPPORT_WINDOWS
#endif // JASMINE_WINDOW
