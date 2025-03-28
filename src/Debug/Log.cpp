#include "glpch.h"

#include "Log.h"

std::shared_ptr<spdlog::logger> API::LogAPI::s_CoreLogger;

void API::LogAPI::Init(const std::shared_ptr<spdlog::sinks::sink>& sharedSink)
{
	std::vector<spdlog::sink_ptr> sinks;

#ifdef DEBUG
	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_pattern("%^[%T.%e] %n: %v%$");
	sinks.push_back(consoleSink);
#endif

	if (sharedSink)
		sinks.push_back(sharedSink);

	s_CoreLogger = std::make_shared<spdlog::logger>("GL_API", sinks.begin(), sinks.end());
	s_CoreLogger->set_level(spdlog::level::trace);
	spdlog::register_logger(s_CoreLogger);
}

void API::LogAPI::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("GL_API");
	s_CoreLogger->set_level(spdlog::level::trace);
}