#pragma once

#include "API/core/RendererAPI.h"

namespace OpenGL::Core {
	class RendererAPI_OpenGL : public API::Core::RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray) override;
		virtual void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& ib) override;
	};
}