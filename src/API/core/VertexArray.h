#pragma once

#include "Buffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <memory>

namespace API::Core {
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) = 0;
		virtual void AddBuffer(const API::Core::Buffer& vb, const API::Core::VertexBufferLayout& layout) = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		inline size_t GetVBCount() const { return vbCount; }
		inline void SetVBCount(size_t count) { vbCount = count; }

		static VertexArray* Create();

	private:
		size_t vbCount = 0;
	};
}
