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

		virtual ~Buffer() = default;

		virtual size_t AddData(const void* data, int size, int offset) = 0;
		virtual size_t AddData(const void* data, int size) = 0;

		virtual void SetData(const void* data, int size) = 0;
		virtual void SetDataDynamic(const void* data, int size) = 0;

		virtual void Empty() = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void BindBase(int slot) const = 0;

		virtual inline size_t getSize() const { return m_BufferSize; };

		static Buffer* Create(BufferType type, const void* data, unsigned int size);
		static Buffer* Create(BufferType type, unsigned int count, size_t elementSize);

	protected:
		size_t m_DataPtr = 0;
		size_t m_BufferSize;
	};
}