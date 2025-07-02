#pragma once

#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace API::Core
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) = 0;
		virtual void AddBuffer(const Buffer& vb, const VertexBufferLayout& layout) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] inline size_t GetVBCount() const { return vbCount; }
		inline void SetVBCount(const size_t count) { vbCount = count; }

		static VertexArray* Create();

	private:
		size_t vbCount = 0;
	};
}
