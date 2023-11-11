#include "glpch.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/Framebuffer_OpenGL.h"

API::Core::Framebuffer* API::Core::Framebuffer::Create(const glm::ivec2& size, bool attachDepth, DepthBufferType depthType)
{
	switch (API::Core::DefaultRendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::Framebuffer_OpenGL(size, attachDepth, depthType);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
