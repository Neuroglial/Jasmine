#pragma once

#include "Jasmine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Jasmine {

	class JASMINE_API Log
	{
	private:
		inline static std::shared_ptr<spdlog::logger> s_CoreLogger;
		inline static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};

}

// Core log macros
#define JM_CORE_TRACE(...)      ::Jasmine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JM_CORE_INFO(...)       ::Jasmine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JM_CORE_WARN(...)       ::Jasmine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JM_CORE_ERROR(...)      ::Jasmine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JM_CORE_CRITICAL(...)   ::Jasmine::Log::GetCoreLogger()->critical(__VA_ARGS__)
							    
// Client log macros		    
#define JM_TRACE(...)           ::Jasmine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JM_INFO(...)            ::Jasmine::Log::GetClientLogger()->info(__VA_ARGS__)
#define JM_WARN(...)            ::Jasmine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JM_ERROR(...)           ::Jasmine::Log::GetClientLogger()->error(__VA_ARGS__)
#define JM_CRITICAL(...)        ::Jasmine::Log::GetClientLogger()->critical(__VA_ARGS__)
