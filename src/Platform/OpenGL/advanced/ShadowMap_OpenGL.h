#pragma once

#include "vendor/glm/glm.hpp"

#include "API/advanced/ShadowMap.h"

namespace OpenGL::Advanced {
	class ShadowMap_OpenGL : public API::Advanced::ShadowMap
	{
	public:
		ShadowMap_OpenGL(const glm::ivec2& size);
		~ShadowMap_OpenGL();

		bool Init(const glm::ivec2& size) override;
		void BindAndClear() override;

		unsigned int BindDepthTexture(const unsigned int slot) override;
		void UnbindDepthTexture() override;

	private:
		unsigned int m_IdFBO;
		unsigned int m_IdDepthBuffer;

		int m_BoundPort;
	};
}