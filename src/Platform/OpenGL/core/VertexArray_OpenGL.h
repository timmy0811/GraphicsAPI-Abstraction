#pragma once

#include "Debug/Debug.h"

#include "API/core/VertexArray.h"
#include "API/core/VertexBuffer.h"
#include "API/core/VertexBufferLayout.h"

namespace OpenGL::Core {
	class VertexArray_OpenGL : public API::Core::VertexArray
	{
	public:
		VertexArray_OpenGL();
		~VertexArray_OpenGL() override;

		void AddBuffer(const API::Core::VertexBuffer& vb, const API::Core::VertexBufferLayout& layout) override;
		void Bind() const override;
		void Unbind() const override;

	private:
		unsigned int m_RendererID;
	};
}
