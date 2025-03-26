#pragma once

#include "Debug/Debug.h"

#include "API/core/Buffer.h"

#include <GL/glew.h>

namespace OpenGL::Core {
	class Buffer_OpenGL : public API::Core::Buffer {
	public:
		Buffer_OpenGL(BufferType type, MemoryLayout layout, const void* data, unsigned int size);
		Buffer_OpenGL(BufferType type, MemoryLayout layout, size_t capacity);
		Buffer_OpenGL(BufferType type, MemoryLayout layout, unsigned int count, size_t elementSize);
		~Buffer_OpenGL() override;

		int AddData(const void* data, size_t size, int offset) override;
		int AddData(const void* data, size_t size) override;

		void SetData(const void* data, size_t size) override;
		void SetDataDynamic(const void* data, size_t size) override;

		void Empty() override;

		void Bind() const override;
		void Unbind() const override;

		void BindBase(int slot) const override;

	private:
		GLenum mapBufferType(BufferType type);
		GLenum mapMemoryLayout(MemoryLayout layout);

	private:
		GLenum type;
		unsigned int m_RendererID;
	};
}