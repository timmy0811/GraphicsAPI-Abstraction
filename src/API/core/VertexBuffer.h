#pragma once

namespace API::Core {

	// Implement this class to add custom addGeometry methods

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void AddVertexData(const void* data, int size, int offset) = 0;
		virtual void AddVertexData(const void* data, int size) = 0;

		virtual void Empty() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual inline size_t getSize() const { return m_DataPtr; };

		static VertexBuffer* Create(const void* data, unsigned int size);
		static VertexBuffer* Create(unsigned int count, size_t elementSize);

	protected:
		size_t m_DataPtr = 0;
		size_t m_BufferSize;
	};
}