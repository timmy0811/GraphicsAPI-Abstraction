#pragma once

#include "API/core/IndexBuffer.h"

namespace OpenGL::Core {
	class IndexBuffer_OpenGL : public API::Core::IndexBuffer {
	public:
		IndexBuffer_OpenGL(const unsigned int* data, unsigned int count);
		~IndexBuffer_OpenGL() override;

		void Bind() const;
		void Unbind() const;

		unsigned int GetCount() const;

	private:
		unsigned int m_RendererID;
	};
}