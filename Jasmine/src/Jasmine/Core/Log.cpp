#include "JM_PCH.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Jasmine {

	void Log::init()
	{
		spdlog::set_pattern("%n %^%T%$ th%t : %^%v%$");
		s_CoreLogger = spdlog::stdout_color_mt("[JMEG]");
		s_CoreLogger->set_level(spdlog::level::trace);
		JM_CORE_INFO("CORE LOG INITIALIZED");

		s_ClientLogger = spdlog::stdout_color_mt("[APP] ");
		s_ClientLogger->set_level(spdlog::level::trace);
		JM_INFO("APP LOG INITIALIZED");		

	}

}