#pragma once

#include "API/core/Shader.h"

namespace API::Advanced {
	class GBufferScreenGeometry
	{
	public:
		virtual ~GBufferScreenGeometry() = default;

		virtual void Draw(Core::Shader* shadingPassShader) = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;

		static GBufferScreenGeometry* Create(unsigned int width, unsigned int height);
	};
}