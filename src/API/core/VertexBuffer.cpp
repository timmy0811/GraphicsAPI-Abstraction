#include "glpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/VertexBuffer_OpenGL.h"

API::Core::VertexBuffer* API::Core::VertexBuffer::Create(const void* data, const unsigned int size)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexBuffer_OpenGL(data, size);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

API::Core::VertexBuffer* API::Core::VertexBuffer::Create(const unsigned int count, const size_t elementSize)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexBuffer_OpenGL(count, elementSize);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

API::Core::VertexBuffer* API::Core::VertexBuffer::Create(const size_t capacity)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::VertexBuffer_OpenGL(capacity);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}