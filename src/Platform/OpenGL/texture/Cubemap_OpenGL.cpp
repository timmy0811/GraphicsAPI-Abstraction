#include <glpch.h>
#include "Cubemap_OpenGL.h"

#include "API/core/RendererCommand.h"
#include "vendor/stb_image/stb_image.h"

#include "GL/glew.h"

OpenGL::Texture::Cubemap_OpenGL::Cubemap_OpenGL(const std::string& dirPath, const std::string& fileFormat)
    :Cubemap(dirPath, fileFormat)
{
    GLCall(glActiveTexture(GL_TEXTURE0));

    GLCall(glGenTextures(1, &InternalId));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, InternalId));

    const std::string imgNames[6] = {
        "px", "nx", "py", "ny", "pz", "nz"
    };

    int width, height, nrChannels, index = 0;
    for (const std::string& imgName : imgNames)
    {
        stbi_set_flip_vertically_on_load(0);
        unsigned char* data = stbi_load((dirPath + '/' + imgName + fileFormat).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            GLenum internalFormat;

            if (nrChannels == 4) {
                format = GL_RGBA;
                internalFormat = GL_RGBA;
            }
            else if (nrChannels == 3) {
                format = GL_RGB;
                internalFormat = GL_RGB;
            }
            else if (nrChannels == 1) {
                format = GL_RED;
                internalFormat = GL_RED;
            }
            else {
                LOG_GL_ERROR("Unsupported channel count: {}", nrChannels);
                stbi_image_free(data);
                continue;
            }

            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index++, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data));
            stbi_image_free(data);
        }
        else {
            LOG_GL_ERROR("Could not load cubemap-image {}", dirPath + '/' + imgName + fileFormat);
        }
    }

    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

OpenGL::Texture::Cubemap_OpenGL::~Cubemap_OpenGL()
{
    GLCall(glDeleteTextures(1, &InternalId));
}

void OpenGL::Texture::Cubemap_OpenGL::Unbind()
{
    GLCall(glActiveTexture(BoundSlot));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
    BoundSlot = -1;
}

unsigned int OpenGL::Texture::Cubemap_OpenGL::Bind(const unsigned int slot)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, InternalId));
    const int slotInt = static_cast<int>(slot);
    BoundSlot = slotInt;

    if (Shader)
    {
        Shader->Bind();
        Shader->SetUniform1i("u_Cubemap", slotInt);
    }

    return slot;
}

void OpenGL::Texture::Cubemap_OpenGL::Render()
{
    if (Shader)
        Shader->Bind();

    GLCall(glDepthFunc(GL_LEQUAL));
    API::Core::RenderCommand::IssueEmptyDrawCall(36);
    GLCall(glDepthFunc(GL_LESS));
}
