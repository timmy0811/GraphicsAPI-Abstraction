#include "glpch.h"
#include "ShadowMap.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/advanced/ShadowMap_OpenGL.h"

inline API::Advanced::ShadowMap* API::Advanced::ShadowMap::Create(const glm::ivec2& size)
{
	switch (API::Core::DefaultRendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Advanced::ShadowMap_OpenGL(size);
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}