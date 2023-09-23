#pragma once

#ifdef JM_DEBUG
	#define JM_ENABLE_ASSERTS
#endif

#ifdef JM_PLATFORM_WINDOWS

#ifdef JM_DYNAMIC_LINK
	#ifdef JM_BUILD_DLL
		#define JASMINE_API _declspec(dllexport)
	#else
		#define JASMINE_API _declspec(dllimport)
	#endif // JASMINE_BUILD_DLL
#else
	#define JASMINE_API
#endif

#else
	#error JASMINE_ONLY_SUPPORT_WINDOWS
#endif // JASMINE_WINDOW


#ifdef JM_ENABLE_ASSERTS
	#define JM_ASSERT(x, ...) { if(!(x)) { JM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JM_CORE_ASSERT(x, ...) { if(!(x)) { JM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JM_ASSERT(x, ...)
	#define JM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x)

#define JM_BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)
#define JM_CONVERT(Type,x) (*(Type*)&x)
