#include "glpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/VertexArray_OpenGL.h"

API::Core::VertexArray* API::Core::VertexArray::Create()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexArray_OpenGL();
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}