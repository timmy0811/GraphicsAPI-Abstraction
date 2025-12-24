#pragma once

#include <array>
#include "vendor/glm/glm.hpp"

namespace API::Advanced
{
    class CascadedShadowMap
    {
    public:
        static constexpr int CascadeCount = 3;

    public:
        virtual ~CascadedShadowMap() = default;

        virtual bool Init(const std::array<glm::ivec2, CascadeCount>& sizes) = 0;

        virtual void BindAndClear(int cascadeIndex) = 0;

        virtual unsigned int BindDepthTexture(int cascadeIndex, unsigned int slot) = 0;
        virtual void UnbindDepthTexture(int cascadeIndex) = 0;

        virtual void Resize(int cascadeIndex, const glm::ivec2& newSize) = 0;

        [[nodiscard]] virtual inline glm::ivec2 GetSize(int cascadeIndex) const = 0;
        [[nodiscard]] virtual inline int GetCascadeCount() const { return CascadeCount; }

        static CascadedShadowMap* Create(const std::array<glm::ivec2, CascadeCount>& sizes);
    };
}
