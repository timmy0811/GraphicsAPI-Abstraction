#pragma once

#ifdef CAST_PLATFORM_WINDOWS
#include "windowsWrapper.hpp"
#endif
#include "Log.h"

#include <iostream>

#ifdef DEBUG
#define GLCall(x) GLCLearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

#define GlCallOnDestruct(x) do { \
    x; \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        std::cerr << "[Termination] OpenGL Error: " << error << " in " << __FILE__ << ":" << __LINE__ << " - " << #x << std::endl; \
    } \
} while (0)

#define LOG(message) std::cout << (message) << std::endl

enum class LOG_COLOR { LOG = 15, WARNING = 14, OK = 10, FAULT = 12, SPECIAL_A = 11, SPECIAL_B = 13 };

#ifdef GLW_PLATFORM_WINDOWS
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
inline void LOGC(const std::string& msg, LOG_COLOR color = LOG_COLOR::LOG) {
	SetConsoleTextAttribute(hConsole, (int)color);
	std::cout << msg << '\n';
	SetConsoleTextAttribute(hConsole, 15);
}

#define ASSERT(x) if(!(x)) __debugbreak();
#define API_ASSERT(x, ...) {if(!(x)) { LOG_GL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#elif GLW_PLATFORM_LINUX
inline void LOGC(const std::string& msg, ...)
{
    std::cout << msg << '\n';
}

#include <csignal>
#define ASSERT(x) if(!(x)) std::raise(SIGTRAP);
#define API_ASSERT(x, ...) {if(!(x)) { LOG_GL_ERROR("Assertion Failed: {0}", __VA_ARGS__); std::raise(SIGTRAP); } }
#endif


void GLCLearError();
bool GLLogCall(const char* function, const char* file, int line);
