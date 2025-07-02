#pragma once

#include "vendor/glm/glm.hpp"
#include "API/advanced/SSAO.h"

#include <vector>

namespace OpenGL::Advanced
{
	class SSAO_OpenGL final : public API::Advanced::SSAO
	{
	public:
		SSAO_OpenGL() = default;

		void GenerateSSAONoiseMap() override;
		void BindNoiseTex(unsigned int slot) override;
	};
}
