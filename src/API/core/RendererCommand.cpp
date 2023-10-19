#include "glpch.h"
#include "RendererCommand.h"

#include "Platform/OpenGL/core/RendererAPI_OpenGL.h"

namespace API::Core {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGL::Core::RendererAPI_OpenGL;
}