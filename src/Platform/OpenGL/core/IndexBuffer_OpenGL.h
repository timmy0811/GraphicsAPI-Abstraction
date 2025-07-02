#pragma once

#include "API/core/IndexBuffer.h"

namespace OpenGL::Core
{
	class IndexBuffer_OpenGL final : public API::Core::IndexBuffer
	{
	public:
		IndexBuffer_OpenGL(const unsigned int* data, unsigned int count);
		~IndexBuffer_OpenGL() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] unsigned int GetCount() const override;

	private:
		unsigned int m_RendererID{};
	};
}
