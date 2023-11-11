#include "glpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/VertexBuffer_OpenGL.h"

API::Core::VertexBuffer* API::Core::VertexBuffer::Create(const void* data, unsigned int size)
{
	switch (API::Core::DefaultRendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexBuffer_OpenGL(data, size);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

API::Core::VertexBuffer* API::Core::VertexBuffer::Create(unsigned int count, size_t elementSize)
{
	switch (API::Core::DefaultRendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexBuffer_OpenGL(count, elementSize);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}