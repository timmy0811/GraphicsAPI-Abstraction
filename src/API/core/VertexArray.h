#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace API::Core {
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexArray* Create();
	};
}
