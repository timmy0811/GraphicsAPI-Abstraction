#include "glpch.h"
#include "Texture.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/texture/Texture_OpenGL.h"

API::Texture::Texture* API::Texture::Texture::Create(const std::string& path, const TextureFilter filter, const bool flipUV)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Texture::Texture_OpenGL(path, filter, flipUV);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}