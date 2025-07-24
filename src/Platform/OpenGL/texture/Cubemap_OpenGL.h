#pragma once

#include "API/texture/Cubemap.h"

namespace OpenGL::Texture
{
    class Cubemap_OpenGL final : public API::Texture::Cubemap
    {
    public:
        Cubemap_OpenGL(const std::string& dirPath, const std::string& fileFormat, bool calcEnvironmentLight);
        ~Cubemap_OpenGL() override;

        void Unbind() override;
        unsigned int Bind(unsigned int slot) override;

        void Render() override;

    private:
        unsigned int InternalId{};
        int BoundSlot = -1;
    };
}
