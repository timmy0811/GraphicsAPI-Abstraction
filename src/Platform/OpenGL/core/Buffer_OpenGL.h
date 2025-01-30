#pragma once

#include "Debug/Debug.h"

#include "API/core/Buffer.h"

#include <GL/glew.h>

namespace OpenGL::Core {
	class Buffer_OpenGL : public API::Core::Buffer {
	public:
		Buffer_OpenGL(BufferType type, const void* data, unsigned int size);
		Buffer_OpenGL(BufferType type, unsigned int count, size_t elementSize);
		~Buffer_OpenGL() override;

		size_t AddData(const void* data, int size, int offset) override;
		size_t AddData(const void* data, int size) override;

		void SetData(const void* data, int size) override;
		void SetDataDynamic(const void* data, int size) override;

		void Empty() override;

		void Bind() const override;
		void Unbind() const override;

		void BindBase(int slot) const override;

	private:
		GLenum mapBufferType(BufferType type);

	private:
		GLenum type;
		unsigned int m_RendererID;
	};
}