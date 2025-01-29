#include "glpch.h"
#include "GBuffer.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/advanced/GBuffer_OpenGL.h"

API::Advanced::GBuffer* API::Advanced::GBuffer::Create(unsigned int width, unsigned int height)
{
	switch (API::Core::DefaultRendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Advanced::GBuffer_OpenGL(width, height);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}