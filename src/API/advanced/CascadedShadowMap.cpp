#include "glpch.h"
#include "CascadedShadowMap.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/advanced/CascadedShadowMap_OpenGL.h"

namespace API::Advanced
{
    CascadedShadowMap* CascadedShadowMap::Create(const std::array<glm::ivec2, CascadeCount>& sizes)
    {
        switch (Core::DefaultRendererContext::GetAPI())
        {
        case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Advanced::CascadedShadowMap_OpenGL(sizes);
        }

        API_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
