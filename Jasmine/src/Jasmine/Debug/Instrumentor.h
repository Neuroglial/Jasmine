#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Jasmine {
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
		//const char* filepath;
	public:
		Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{
		}

		void BeginSession(const std::string& name, const char* filepath = "results.json")
		{
			//this->filepath = filepath;
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",\n";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[\n";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "\n]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_Name(name), m_Stopped(false)
		{
			auto now = std::chrono::high_resolution_clock::now();
			start = std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count();
			threadID = std::hash<std::thread::id>()(std::this_thread::get_id());

			
			auto Last = m_LastTime.find(threadID);

			if (Last != m_LastTime.end()) {
				if (Last->second >= start)
					start = Last->second + 1;
				Last->second = start;
			}
			else m_LastTime[threadID] = start;
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
			m_Stopped = true;
		}
	private:
		const char* m_Name;
		long long start;
		inline static std::unordered_map<uint32_t, long long> m_LastTime = std::unordered_map<uint32_t, long long>();
		uint32_t threadID;
		bool m_Stopped;
	};
}

#define JM_PROFILE 1
#if JM_PROFILE
	#define JM_PROFILE_BEGIN_SESSION(name, filepath) ::Jasmine::Instrumentor::Get().BeginSession(name, filepath)
	#define JM_PROFILE_END_SESSION() ::Jasmine::Instrumentor::Get().EndSession()
	#define JM_PROFILE_SCOPE(name) ::Jasmine::InstrumentationTimer timer##__LINE__(name);
	#define JM_PROFILE_FUNCTION() JM_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define JM_PROFILE_BEGIN_SESSION(name, filepath)
	#define JM_PROFILE_END_SESSION()
	#define JM_PROFILE_SCOPE(name)
	#define JM_PROFILE_FUNCTION()
#endif