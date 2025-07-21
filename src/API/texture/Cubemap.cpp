#include "glpch.h"
#include "Cubemap.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/texture/Cubemap_OpenGL.h"

API::Texture::Cubemap::Cubemap(const std::string& dirPath, const std::string& fileFormat)
    :DirPath(dirPath), FileFormat(fileFormat)
{
}

API::Texture::Cubemap* API::Texture::Cubemap::Create(const std::string& dirPath, const std::string& fileFormat)
{
    switch (Core::DefaultRendererContext::GetAPI())
    {
    case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Texture::Cubemap_OpenGL(dirPath, fileFormat);
    }

    API_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
