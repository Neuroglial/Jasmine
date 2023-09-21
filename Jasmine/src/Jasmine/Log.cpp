#include "JM_PCH.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Jasmine {

	void Log::init()
	{
		spdlog::set_pattern("[%n] [%^%T%$] [thread %t] : %^%v%$");
		s_CoreLogger = spdlog::stdout_color_mt("JASMINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}

}