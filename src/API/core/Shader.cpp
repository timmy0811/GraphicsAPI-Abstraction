#include "glpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/core/Shader_OpenGL.h"

API::Core::Shader* API::Core::Shader::Create(const std::string& path_vert, const std::string& path_frag)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Core::Shader_OpenGL(path_vert, path_frag);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}