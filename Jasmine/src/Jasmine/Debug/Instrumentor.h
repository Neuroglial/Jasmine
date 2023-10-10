#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <stdarg.h>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <list>
#include <mutex>

#include <thread>


#define JM_PROFILE 0
#define JM_DEBUG_FSTREAM 0
#define INSTRUMENTOR_MUTITHRESD 1


#if JM_DEBUG_FSTREAM
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
#else
namespace Jasmine {

	struct ProfileResult
	{
		const char* Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};


#if INSTRUMENTOR_MUTITHRESD

	class Instrumentor
	{
	public:
		Instrumentor()
		{
		}

		void BeginSession(const std::string& name, const char* filepath = "results.json")
		{
			fopen_s(&fptr, filepath, "w");
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
			BeginThread();
		}

		void EndSession()
		{
			EndThread();
			WriteFooter();
			FlushBuffer();
			fclose(fptr);
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
			BufferPointer = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			prolock.lock();
			prolist.push_back(result);
			prolock.unlock();

			prosize.fetch_add(1);
		}

		void WriteHeader()
		{
			bufferPrintf("{\"otherData\": {},\"traceEvents\":[\n");
		}

		void WriteFooter()
		{
			bufferPrintf("\n]}");
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}


	private:
		void BeginThread() {
			ThreadContinue = true;
			prosize.store(0);
			theThread = new std::thread(&Instrumentor::BufferThread, this);
		}

		void EndThread() {
			ThreadContinue = false;
			theThread->join();
			delete theThread;
			theThread = nullptr;
		}

		void BufferThread() {
			static ProfileResult re;
			int size = 0;

			while (ThreadContinue || prosize.load()) {
				if (prosize.load()) {

					prolock.lock();
					re = prolist.front();
					prolist.pop_front();
					prolock.unlock();

					prosize.fetch_sub(1);
					writeResult(re);
				}
				else {
					std::this_thread::yield();
				}
			}
		}

	private:
		inline void FlushBuffer() {
			fputs(Buffer, fptr);
			BufferPointer = 0;
		}

		template<typename ...Args>
		void bufferPrintf(const char* _Format, Args... args) {
			BufferPointer += sprintf_s(&Buffer[BufferPointer], MAXBUFFER - BufferPointer, _Format, args...);
			if (BufferPointer >= MAXBUFFER * 0.75)
				FlushBuffer();
		}

		//void bufferPrintf(const char* _Format, ...) {
		//	va_list args;
		//	va_start(args, _Format);
		//	BufferPointer += vsprintf_s(&Buffer[BufferPointer], MAXBUFFER - BufferPointer, _Format, args);
		//	va_end(args);
		//	if (BufferPointer >= MAXBUFFER * 0.75)
		//		FlushBuffer();
		//}

		void writeResult(ProfileResult& result) {
			const char* name = result.Name;
			//std::replace(name.begin(), name.end(), '"', '\'');

			if (m_ProfileCount++ > 0)
				bufferPrintf(",\n");

			bufferPrintf("{\"cat\":\"function\",\"dur\":%lld,\"name\":\"%s\",\"ph\":\"X\",\"pid\":0,\"tid\":%u,\"ts\":%lld}",
				(result.End - result.Start), name, result.ThreadID, result.Start);
		}

	private:
		InstrumentationSession* m_CurrentSession = nullptr;
		//std::ofstream m_OutputStream;
		inline static const unsigned MAXBUFFER = 4096;
		int m_ProfileCount = 0;
		FILE* fptr;
		char Buffer[MAXBUFFER];
		unsigned BufferPointer = 0;

		std::list<ProfileResult> prolist;
		std::mutex prolock;
		std::atomic<unsigned> prosize;

		std::thread* theThread;
		bool ThreadContinue;
	};

#else
	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession = nullptr;
		//std::ofstream m_OutputStream;
		inline static const unsigned MAXBUFFER = 2048;
		int m_ProfileCount = 0;
		FILE* fptr;
		char Buffer[MAXBUFFER];
		unsigned BufferPointer = 0;

	public:
		Instrumentor()
		{
		}

		void BeginSession(const std::string& name, const char* filepath = "results.json")
		{
			fopen_s(&fptr, filepath, "w");
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			FlushBuffer();
			fclose(fptr);
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
			BufferPointer = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			const char* name = result.Name;
			//std::replace(name.begin(), name.end(), '"', '\'');

			if (m_ProfileCount++ > 0)
				bufferPrintf(",\n");

			bufferPrintf("{\"cat\":\"function\",\"dur\":%lld,\"name\":\"%s\",\"ph\":\"X\",\"pid\":0,\"tid\":%u,\"ts\":%lld}",
				(result.End - result.Start), name, result.ThreadID, result.Start);
		}

		void WriteHeader()
		{
			bufferPrintf("{\"otherData\": {},\"traceEvents\":[\n");
		}

		void WriteFooter()
		{
			bufferPrintf("\n]}");
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	private:
		inline void FlushBuffer() {
			fputs(Buffer, fptr);
			BufferPointer = 0;
		}

		void bufferPrintf(const char* _Format, ...) {
			va_list args;
			va_start(args, _Format);
			BufferPointer += vsprintf_s(&Buffer[BufferPointer], MAXBUFFER - BufferPointer, _Format, args);
			va_end(args);
			if (BufferPointer >= MAXBUFFER * 0.75)
				FlushBuffer();
		}

	};
#endif


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
#endif

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