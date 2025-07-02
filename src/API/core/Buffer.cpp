#include "glpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/Buffer_OpenGL.h"

API::Core::Buffer* API::Core::Buffer::Create(const BufferType type, const MemoryLayout layout, const void* data,
                                             const unsigned int size)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None: API_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
	case RendererAPI::API_ENUM::OpenGL: return new OpenGL::Core::Buffer_OpenGL(type, layout, data, size);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

API::Core::Buffer* API::Core::Buffer::Create(const BufferType type, const MemoryLayout layout, const size_t capacity)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None: API_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
	case RendererAPI::API_ENUM::OpenGL: return new OpenGL::Core::Buffer_OpenGL(type, layout, capacity);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

API::Core::Buffer* API::Core::Buffer::Create(const BufferType type, const MemoryLayout layout, const unsigned int count,
                                             const size_t elementSize)
{
	switch (DefaultRendererContext::GetAPI())
	{
	case RendererAPI::API_ENUM::None: API_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
	case RendererAPI::API_ENUM::OpenGL: return new OpenGL::Core::Buffer_OpenGL(
			type, layout, count, elementSize);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
