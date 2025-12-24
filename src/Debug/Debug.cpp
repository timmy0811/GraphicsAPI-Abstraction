#include "glpch.h"
#include "Debug.h"

#include <GL/glew.h>

void GLCLearError()
{
    // Drain all pending GL errors so that the next GLCall reports only
    // errors from the call being wrapped, not some previous unrelated call.
    while (glGetError() != GL_NO_ERROR) {}
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