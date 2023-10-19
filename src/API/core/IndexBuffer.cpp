#include "glpch.h"
#include "IndexBuffer.h"

#include "Debug/Debug.h"
#include "Renderer.h"
#include "Platform/OpenGL/core/IndexBuffer_OpenGL.h"

API::Core::IndexBuffer* API::Core::IndexBuffer::Create(const unsigned int* data, unsigned int count)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::IndexBuffer_OpenGL(data, count);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}