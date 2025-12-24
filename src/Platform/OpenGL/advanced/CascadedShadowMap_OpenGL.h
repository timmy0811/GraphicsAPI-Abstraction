#pragma once

#include <array>

#include "vendor/glm/glm.hpp"
#include <GL/glew.h>

#include "API/advanced/CascadedShadowMap.h"

namespace OpenGL::Advanced
{
    class CascadedShadowMap_OpenGL final : public API::Advanced::CascadedShadowMap
    {
    public:
        explicit CascadedShadowMap_OpenGL(const std::array<glm::ivec2, CascadeCount>& sizes)
        {
            Init(sizes);
        }
        ~CascadedShadowMap_OpenGL() override;

        bool Init(const std::array<glm::ivec2, CascadeCount>& sizes) override;

        void BindAndClear(int cascadeIndex) override;

        unsigned int BindDepthTexture(int cascadeIndex, unsigned int slot) override;
        void UnbindDepthTexture(int cascadeIndex) override;

        void Resize(int cascadeIndex, const glm::ivec2& newSize) override;

        inline glm::ivec2 GetSize(int cascadeIndex) const override { return m_Sizes[cascadeIndex]; }

    private:
        bool CreateCascade(int i, const glm::ivec2& size);
        void DestroyCascade(int i);

    private:
        struct Cascade
        {
            GLuint fbo = 0;
            GLuint depthTex = 0;
            int boundSlot = -1;
        };

        std::array<Cascade, CascadeCount> m_Cascades{};
        std::array<glm::ivec2, CascadeCount> m_Sizes{};
    };
}
