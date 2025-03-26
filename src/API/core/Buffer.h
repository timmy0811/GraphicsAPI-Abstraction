#pragma once

namespace API::Core {
	class Buffer {
	public:
		enum BufferType {
			SHADER_STORAGE_BUFFER,
			ARRAY_BUFFER,
			ELEMENT_ARRAY_BUFFER,
			UNIFORM_BUFFER,
			ATOMIC_COUNTER_BUFFER,
			DRAW_INDIRECT_BUFFER,
			DISPATCH_INDIRECT_BUFFER,
			COPY_READ_BUFFER,
			COPY_WRITE_BUFFER,
			PIXEL_PACK_BUFFER,
			PIXEL_UNPACK_BUFFER,
			TRANSFORM_FEEDBACK_BUFFER,
			TEXTURE_BUFFER
		};

		enum MemoryLayout {
			STATIC,
			DYNAMIC
		};

		virtual ~Buffer() = default;

		virtual int AddData(const void* data, size_t size, int offset) = 0;
		virtual int AddData(const void* data, size_t size) = 0;

		virtual void SetData(const void* data, size_t size) = 0;
		virtual void SetDataDynamic(const void* data, size_t size) = 0;

		virtual void Empty() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void BindBase(int slot) const = 0;

		virtual inline size_t GetCapacity() const { return m_BufferSize; };
		virtual inline size_t GetSize() const { return m_DataPtr; };

		static Buffer* Create(BufferType type, MemoryLayout layout, const void* data, unsigned int size);
		static Buffer* Create(BufferType type, MemoryLayout layout, size_t capacity);
		static Buffer* Create(BufferType type, MemoryLayout layout, unsigned int count, size_t elementSize);

	protected:
		size_t m_DataPtr = 0;
		size_t m_BufferSize;
	};
}