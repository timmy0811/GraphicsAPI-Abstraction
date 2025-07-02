#include "glpch.h"
#include "Debug.h"

#include <GL/glew.h>

void GLCLearError()
{
}

bool GLLogCall(const char* function, const char* file, const int line)
{
	while (const GLenum error = glGetError()) {
		std::stringstream ss;
		ss << "[OpenGL Error] (" << error << "): " << function << " " << file << ": line " << line << std::endl;
		LOG_GL_ERROR("{}", ss.str());
		return false;
	}
	return true;
}