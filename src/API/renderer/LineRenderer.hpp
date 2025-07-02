#pragma once

#include "API/core/Renderer.h"
#include "Misc/structs/Primitive.hpp"

#include "API/core/VertexBuffer.h"
#include "API/core/VertexArray.h"
#include "API/core/IndexBuffer.h"
#include "API/core/VertexBufferLayout.h"
#include "API/core/Shader.h"

#include "API/legacy/LegacyRenderer.h"

#include <GL/glew.h>

#include <memory>
#include <string>

namespace API::Misc
{
	class LineRenderer
	{
	public:
		std::shared_ptr<Core::VertexBuffer> vb;
		std::shared_ptr<Core::IndexBuffer> ib;
		std::shared_ptr<Core::VertexBufferLayout> vbLayout;
		std::shared_ptr<Core::VertexArray> va;

		std::shared_ptr<Core::Shader> shader;

		LineRenderer(const int count, const glm::vec4 color, const std::string& shaderVert, const std::string& shaderFrag)
			: shader(Core::Shader::Create(shaderVert, shaderFrag))
		{
			auto indices = new unsigned int[count];

			for (int i = 0; i < count; i++)
			{
				indices[i] = i;
			}

			ib.reset(Core::IndexBuffer::Create(indices, count));
			vb.reset(Core::VertexBuffer::Create(count, sizeof(primitive::vertex::Vertex3D)));

			delete[] indices;

			vbLayout.reset(Core::VertexBufferLayout::Create());
			vbLayout->Push(Core::ShaderDataType::Float3);

			va.reset(Core::VertexArray::Create());
			va->AddBuffer(*vb, *vbLayout);

			shader->Bind();
			shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
		}

		~LineRenderer()
		{
		}

		inline void Draw() const
		{
			GLCall(glLineWidth(3));
			shader->Bind();
			va->Bind();
			ib->Bind();
			Legacy::LegacyRenderer::Draw(*va, *ib, *shader, GL_LINES);
		}

		inline void DrawInstanced(const unsigned int count, const unsigned int instances) const
		{
			GLCall(glLineWidth(3));
			Legacy::LegacyRenderer::Draw(*va, *ib, *shader, count, instances);
		}
	};
}
