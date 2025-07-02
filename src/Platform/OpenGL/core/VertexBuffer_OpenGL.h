#pragma once

#include "API/core/VertexBuffer.h"

namespace OpenGL::Core
{
	class VertexBuffer_OpenGL final : public API::Core::VertexBuffer
	{
	public:
		VertexBuffer_OpenGL(const void* data, unsigned int size);
		VertexBuffer_OpenGL(unsigned int count, size_t elementSize);
		explicit VertexBuffer_OpenGL(size_t capacity);
		~VertexBuffer_OpenGL() override;

		int AddVertexData(const void* data, int size, int offset) override;
		int AddVertexData(const void* data, int size) override;

		void Empty() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		unsigned int m_RendererID = 0;
	};
}
