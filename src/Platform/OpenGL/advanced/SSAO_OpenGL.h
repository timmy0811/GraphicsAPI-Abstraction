#pragma once

#include "vendor/glm/glm.hpp"
#include "API/advanced/SSAO.h"

#include <vector>

namespace OpenGL::Advanced {
	class SSAO_OpenGL : public API::Advanced::SSAO
	{
	public:
		SSAO_OpenGL() 
			:API::Advanced::SSAO() {}

		void GenerateSSAONoiseMap() override;
		void BindNoiseTex(const unsigned int slot) override;
	};
}