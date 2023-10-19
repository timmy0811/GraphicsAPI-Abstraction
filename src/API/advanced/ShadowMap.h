#pragma once

#include "vendor/glm/glm.hpp"

namespace API::Advanced {
	class ShadowMap
	{
	public:
		virtual ~ShadowMap() = default;

		virtual bool Init(const glm::ivec2& size) = 0;
		virtual void BindAndClear() = 0;

		virtual unsigned int BindDepthTexture(const unsigned int slot) = 0;
		virtual void UnbindDepthTexture() = 0;

		virtual inline void Resize(const glm::ivec2& size) { m_Width = size.x; m_Height = size.y; }

		static inline ShadowMap* Create(const glm::ivec2& size);

	protected:
		unsigned int m_Width, m_Height;
	};
}