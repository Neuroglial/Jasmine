#pragma once
#include <memory>
#include "Jasmine/Core/PlatformDetection.h"

#ifdef JM_DEBUG
#if defined(JM_PLATFORM_WINDOWS)
#define JM_DEBUGBREAK() __debugbreak()
#elif defined(JM_PLATFORM_LINUX)
#include <signal.h>
#define JM_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define JM_ENABLE_ASSERTS
#else
#define JM_DEBUGBREAK()
#endif
// TODO: Make this macro able to take in no arguments except condition
#ifdef JM_ENABLE_ASSERTS
#define JM_ASSERT(x, ...) { if(!(x)) { JM_ERROR("Assertion Failed: {0}", __VA_ARGS__); JM_DEBUGBREAK(); } }
#define JM_CORE_ASSERT(x, ...) { if(!(x)) { JM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); JM_DEBUGBREAK(); } }
#else
#define JM_ASSERT(x, ...)
#define JM_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)
#define JM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
namespace Jasmine {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#define JM_BIND_FN(x) std::bind(&x,this,std::placeholders::_1)
#define JM_CONVERT(Type,x) (*(Type*)&x)

#define JM_SP(T) std::shared_ptr<T>
#define JM_CSP(T) std::make_shared<T>
#define JM_UP(T) std::unique_ptr<T>
#define JM_CUP(T) std::make_unique<T>