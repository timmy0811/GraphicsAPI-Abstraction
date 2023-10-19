#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "API/core/Shader.h"
#include "API/legacy/LegacyRenderer.h"
#include "Primitive.hpp"

#include <GLEW/glew.h>

namespace API::Misc {
	struct Vec2_4 {
		glm::vec2 u0;
		glm::vec2 u1;
		glm::vec2 u2;
		glm::vec2 u3;
	};

	struct SymbolInformation {
		Vec2_4 uv;
		unsigned int width;
	};

	struct ScreenQuad {
		ScreenQuad(glm::vec2 winSize)
		{
			m_MatProjectionVertex = glm::ortho(0.0f, winSize.x, 0.0f, winSize.y, -1.0f, 1.0f);

			unsigned int index[] = {
				0, 1, 2, 2, 3, 0
			};

			m_IndexBuffer = std::make_unique<Core::IndexBuffer>(index, 6);
			m_VertexBuffer = std::make_unique<Core::VertexBuffer>(4, sizeof(primitive::vertex::Vertex3D));

			primitive::vertex::Vertex3D vert[] = {
				glm::vec3(-1.f, -1.f, 0.f),
				glm::vec3(1.f, -1.f, 0.f),
				glm::vec3(1.f, 1.f, 0.f),
				glm::vec3(-1.f, 1.f, 0.f)
			};

			m_VertexBuffer->Bind();
			m_VertexBuffer->AddVertexData(vert, sizeof(primitive::vertex::Vertex3D) * 4);

			m_VertexBufferLayout = std::make_unique<Core::VertexBufferLayout>();
			m_VertexBufferLayout->Push(API::Core::ShaderDataType::Float3);

			m_VertexArray = std::make_unique<Core::VertexArray>();
			m_VertexArray->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
		}

		void Draw(const Core::Shader& shader) {
			API::Legacy::LegacyRenderer::Draw(*m_VertexArray, *m_IndexBuffer, shader, GL_TRIANGLES, 6);
		}

		// Only used for custom dimensions
		void SetProjectionMat(Core::Shader& shader) {
			shader.Bind();
			shader.SetUniformMat4f("u_ScreenQuadProj", m_MatProjectionVertex);
		}

		std::unique_ptr<Core::VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Core::IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Core::VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<Core::VertexArray> m_VertexArray;

		glm::mat4 m_MatProjectionVertex;
	};

	// Functions
	static int mapRGBToInt(const glm::vec3& color)
	{
		int r = int(color.r * 255) << 16;
		int g = int(color.g * 255) << 8;
		int b = int(color.b * 255);

		return r | g | b;
	}
}