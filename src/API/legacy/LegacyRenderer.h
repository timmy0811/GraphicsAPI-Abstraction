#pragma once

#include "API/core/VertexArray.h"
#include "API/core/IndexBuffer.h"
#include "API/core/Shader.h"

namespace API::Legacy {
	class LegacyRenderer {
	public:
		static void Init();
		static void BindOrigFramebuffer();

		static void Clear();
		static void ClearDepthBufferOnly();

		static void Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, int mode = 0x0004, int count = -1);
		static void Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, size_t count);
		static void DrawArray(const Core::VertexArray& va, const Core::Shader& shader, size_t first, size_t count);
		static void DrawInstancedLines(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, size_t count, size_t instances);

	public:
		static inline int FramebufferOriginId;
	};
}