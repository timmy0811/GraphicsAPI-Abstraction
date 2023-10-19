#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace API {
	class LogAPI
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }

		inline static void SetCoreLogLevel(spdlog::level::level_enum level) { s_CoreLogger->set_level(level); }

		inline static void SetCoreLogPattern(const std::string& pattern) { s_CoreLogger->set_pattern(pattern); }

		inline static void FlushLogsPeriodically(unsigned int seconds) { spdlog::flush_every(std::chrono::seconds(seconds)); }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

#define LOG_GL_FATAL(...) ::API::LogAPI::GetCoreLogger()->fatal(__VA_ARGS__)
#define LOG_GL_ERROR(...) ::API::LogAPI::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_GL_WARN(...) ::API::LogAPI::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_GL_INFO(...) ::API::LogAPI::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_GL_TRACE(...) ::API::LogAPI::GetCoreLogger()->trace(__VA_ARGS__)

#define LOG_GL_START_LOCAL_SW(name) spdlog::stopwatch name
#define LOG_GL_SW_ELAPSED(name) spdlog::debug("Elapsed {0}", name)