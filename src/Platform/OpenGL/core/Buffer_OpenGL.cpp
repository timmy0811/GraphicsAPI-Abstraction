#include "glpch.h"
#include "Buffer_OpenGL.h"

#include "Debug/Debug.h"
#include "GL/glew.h"

OpenGL::Core::Buffer_OpenGL::Buffer_OpenGL(const BufferType type, const MemoryLayout layout, const void* data, const unsigned int size)
{
	this->type = mapBufferType(type);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(this->type, m_RendererID));
	GLCall(glBufferData(this->type, size, data, mapMemoryLayout(layout)));

	m_BufferSize = (size_t)size;
}

OpenGL::Core::Buffer_OpenGL::Buffer_OpenGL(const BufferType type, const MemoryLayout layout, const size_t capacity)
{
	this->type = mapBufferType(type);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(this->type, m_RendererID));
	GLCall(glBufferData(this->type, capacity, nullptr, mapMemoryLayout(layout)));

	m_BufferSize = capacity;
}

OpenGL::Core::Buffer_OpenGL::Buffer_OpenGL(const BufferType type, const MemoryLayout layout, const unsigned int count, const size_t elementSize)
{
	this->type = mapBufferType(type);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(this->type, m_RendererID));
	GLCall(glBufferData(this->type, (size_t)count * elementSize, nullptr, mapMemoryLayout(layout)));

	m_BufferSize = (size_t)count * elementSize;
}

int OpenGL::Core::Buffer_OpenGL::AddData(const void* data, const size_t size, const int offset)
{
	if (offset + size > m_BufferSize)
	{
		LOG_GL_ERROR("OpenGL Buffer exceeding its capacity by " + std::to_string(offset + size - m_BufferSize) + " Bytes. Adding of new data is canceled.");
		return -1;
	}

	Bind();
	GLCall(glBufferSubData(this->type, offset, size, data));

	return offset;
}

int OpenGL::Core::Buffer_OpenGL::AddData(const void* data, const size_t size)
{
	if (m_DataPtr + size > m_BufferSize)
	{
		LOG_GL_ERROR("OpenGL Buffer exceeding its capacity by " + std::to_string(m_DataPtr + size - m_BufferSize) + " Bytes. Adding of new data is canceled.");
		return -1;
	}

	Bind();
	GLCall(glBufferSubData(this->type, (long)m_DataPtr, size, data));
	m_DataPtr += size;

	return (int)(m_DataPtr - size);
}

void OpenGL::Core::Buffer_OpenGL::SetData(const void* data, const size_t size)
{
	Bind();
	GLCall(glBufferData(this->type, size, data, GL_STATIC_DRAW));
}

void OpenGL::Core::Buffer_OpenGL::SetDataDynamic(const void* data, const size_t size)
{
	Bind();
	GLCall(glBufferData(this->type, size, data, GL_DYNAMIC_DRAW));
}

void OpenGL::Core::Buffer_OpenGL::Empty()
{
	Bind();
	GLCall(glBufferSubData(this->type, 0, m_BufferSize, nullptr));
	m_DataPtr = 0;
}

void OpenGL::Core::Buffer_OpenGL::EmptyPastOffset(const size_t offset)
{
	Bind();
	GLCall(glBufferSubData(this->type, offset, m_BufferSize - offset, nullptr));
	m_DataPtr = offset;
}

OpenGL::Core::Buffer_OpenGL::~Buffer_OpenGL()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGL::Core::Buffer_OpenGL::Bind() const
{
	GLCall(glBindBuffer(this->type, m_RendererID));
}

void OpenGL::Core::Buffer_OpenGL::Unbind() const
{
	GLCall(glBindBuffer(this->type, 0));
}

void OpenGL::Core::Buffer_OpenGL::BindBase(const int slot) const
{
	GLCall(glBindBufferBase(this->type, slot, m_RendererID));
}

GLenum OpenGL::Core::Buffer_OpenGL::mapBufferType(const BufferType type)
{
	switch (type)
	{
	case SHADER_STORAGE_BUFFER: return GL_SHADER_STORAGE_BUFFER;
	case ARRAY_BUFFER: return GL_ARRAY_BUFFER;
	case ELEMENT_ARRAY_BUFFER: return GL_ELEMENT_ARRAY_BUFFER;
	case UNIFORM_BUFFER: return GL_UNIFORM_BUFFER;
	case ATOMIC_COUNTER_BUFFER: return GL_ATOMIC_COUNTER_BUFFER;
	case DRAW_INDIRECT_BUFFER: return GL_DRAW_INDIRECT_BUFFER;
	case DISPATCH_INDIRECT_BUFFER: return GL_DISPATCH_INDIRECT_BUFFER;
	case COPY_READ_BUFFER: return GL_COPY_READ_BUFFER;
	case COPY_WRITE_BUFFER: return GL_COPY_WRITE_BUFFER;
	case PIXEL_PACK_BUFFER: return GL_PIXEL_PACK_BUFFER;
	case PIXEL_UNPACK_BUFFER: return GL_PIXEL_UNPACK_BUFFER;
	case TRANSFORM_FEEDBACK_BUFFER: return GL_TRANSFORM_FEEDBACK_BUFFER;
	case TEXTURE_BUFFER: return GL_TEXTURE_BUFFER;
	default: return GL_NONE;
	}
}

GLenum OpenGL::Core::Buffer_OpenGL::mapMemoryLayout(const MemoryLayout layout)
{
	switch (layout)
	{
	case STATIC: return GL_STATIC_DRAW;
	case DYNAMIC: return GL_DYNAMIC_DRAW;
	default: return GL_NONE;
	}
}
