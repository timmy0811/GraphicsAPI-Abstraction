#include "glpch.h"
#include "GBufferScreenGeometry.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/advanced/GBufferScreenGeometry_OpenGL.h"

API::Advanced::GBufferScreenGeometry* API::Advanced::GBufferScreenGeometry::Create(const unsigned int width, const unsigned int height)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Advanced::GBufferScreenGeometry_OpenGL(width, height);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}