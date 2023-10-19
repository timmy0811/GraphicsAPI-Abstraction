#pragma once

#include "Debug/Debug.h"

#include "API/core/VertexBuffer.h"

namespace OpenGL::Core {
	class VertexBuffer_OpenGL : public API::Core::VertexBuffer{
	public:
		VertexBuffer_OpenGL(const void* data, unsigned int size);
		VertexBuffer_OpenGL(unsigned int count, size_t elementSize);
		~VertexBuffer_OpenGL() override;

		void AddVertexData(const void* data, int size, int offset) override;
		void AddVertexData(const void* data, int size) override;

		void Empty() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		unsigned int m_RendererID;
	};
}