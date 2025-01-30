#include "glpch.h"
#include "Buffer_OpenGL.h"

OpenGL::Core::Buffer_OpenGL::Buffer_OpenGL(BufferType type, const void* data, unsigned int size)
{
	this->type = mapBufferType(type);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(this->type, m_RendererID));
	GLCall(glBufferData(this->type, size, data, GL_STATIC_DRAW));

	m_BufferSize = (size_t)size;
}

OpenGL::Core::Buffer_OpenGL::Buffer_OpenGL(BufferType type, unsigned int count, size_t elementSize)
{
	this->type = mapBufferType(type);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(this->type, m_RendererID));
	GLCall(glBufferData(this->type, (size_t)count * elementSize, nullptr, GL_DYNAMIC_DRAW));

	m_BufferSize = (size_t)count * elementSize;
}

size_t OpenGL::Core::Buffer_OpenGL::AddData(const void* data, int size, int offset) {
	Bind();
	GLCall(glBufferSubData(this->type, offset, size, data));

	return offset;
}

size_t OpenGL::Core::Buffer_OpenGL::AddData(const void* data, int size) {
	Bind();
	GLCall(glBufferSubData(this->type, m_DataPtr, size, data));
	m_DataPtr += size;

	return m_DataPtr;
}

void OpenGL::Core::Buffer_OpenGL::SetData(const void* data, int size)
{
	Bind();
	GLCall(glBufferData(this->type, size, data, GL_STATIC_DRAW));
}

void OpenGL::Core::Buffer_OpenGL::SetDataDynamic(const void* data, int size)
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

void OpenGL::Core::Buffer_OpenGL::BindBase(int slot) const
{
	GLCall(glBindBufferBase(this->type, 1, m_RendererID))
}

GLenum OpenGL::Core::Buffer_OpenGL::mapBufferType(BufferType type)
{
	switch (type) {
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