#include "glpch.h"
#include "VertexBufferLayout.h"

#include "API/core/Renderer.h"

#include <GLEW/glew.h>

API::Core::VertexBufferLayout* API::Core::VertexBufferLayout::Create()
{
	return new API::Core::VertexBufferLayout();
}

int API::Core::VertexBufferElement::GetAPIDataType(ShaderDataType dataType)
{
	switch (RendererContext::GetAPI()) {
	case RendererAPI::API_ENUM::None:
		API_ASSERT(false, "RendererAPI::None is currently not supported!");
		return 0;
	case RendererAPI::API_ENUM::OpenGL:
		switch (dataType)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}
		API_ASSERT(false, "Unknown Buffer Element Type.");
	}
	return 0;
}