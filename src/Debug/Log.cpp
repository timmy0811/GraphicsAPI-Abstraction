#include "glpch.h"

#include "Log.h"

std::shared_ptr<spdlog::logger> API::LogAPI::s_CoreLogger;

void API::LogAPI::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("GL_API");
	s_CoreLogger->set_level(spdlog::level::trace);
}