#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Jasmine {
	void Jasmine::Log::init()
	{
		//spdlog::set_pattern("%^[%T] %n: %v%$");
		spdlog::set_pattern("[%n] [%^%T%$] [thread %t] : %^%v%$");

		s_CoreLogger = spdlog::stdout_color_mt("JASMINE");
		s_CoreLogger->set_level(spdlog::level::level_enum::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::level_enum::trace);

	}
}