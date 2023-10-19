#pragma once

#include <vendor/glm/glm.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"

namespace API::Core {
	class RendererAPI
	{
	public:
		enum class API_ENUM
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		inline static API_ENUM GetAPI() { return s_API; }
	private:
		static API_ENUM s_API;
	};
}