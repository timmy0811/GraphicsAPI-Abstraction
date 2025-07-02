#pragma once

#include "API/advanced/GBufferScreenGeometry.h"

#include <API/core/IndexBuffer.h>
#include <API/core/Shader.h>
#include <API/core/VertexArray.h>
#include <API/core/VertexBuffer.h>
#include <API/core/VertexBufferLayout.h>

#include "API/advanced/GBufferScreenGeometry.h"

namespace OpenGL::Advanced
{
	class GBufferScreenGeometry_OpenGL final : public API::Advanced::GBufferScreenGeometry
	{
	public:
		GBufferScreenGeometry_OpenGL(unsigned int width, unsigned int height);
		~GBufferScreenGeometry_OpenGL() override = default;

		void Draw(API::Core::Shader* shadingPassShader) override;
		void Resize(unsigned int width, unsigned int height) override;

	private:
		unsigned int Width, Height;

		std::unique_ptr<API::Core::VertexBuffer> VBO;
		std::unique_ptr<API::Core::IndexBuffer> IBO;
		std::unique_ptr<API::Core::VertexBufferLayout> VBL;
		std::unique_ptr<API::Core::VertexArray> VAO;

		glm::mat4 ProjectionMat{};
	};
}
