#include "glpch.h"
#include "VertexBuffer_OpenGL.h"

#include <GL/glew.h>

OpenGL::Core::VertexBuffer_OpenGL::VertexBuffer_OpenGL(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

	m_BufferSize = (size_t)size;
	m_DataPtr += size;
}

OpenGL::Core::VertexBuffer_OpenGL::VertexBuffer_OpenGL(unsigned int count, size_t elementSize)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, (size_t)count * elementSize, nullptr, GL_DYNAMIC_DRAW));

	m_BufferSize = (size_t)count * elementSize;
}

OpenGL::Core::VertexBuffer_OpenGL::VertexBuffer_OpenGL(size_t capacity)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, capacity, nullptr, GL_DYNAMIC_DRAW));

	m_BufferSize = capacity;
}

int OpenGL::Core::VertexBuffer_OpenGL::AddVertexData(const void* data, int size, int offset) {
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));

	return offset;
}

int OpenGL::Core::VertexBuffer_OpenGL::AddVertexData(const void* data, int size) {
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, m_DataPtr, size, data));
	m_DataPtr += size;

	return m_DataPtr - size;
}

void OpenGL::Core::VertexBuffer_OpenGL::Empty()
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_BufferSize, nullptr));
	m_DataPtr = 0;
}

OpenGL::Core::VertexBuffer_OpenGL::~VertexBuffer_OpenGL()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGL::Core::VertexBuffer_OpenGL::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void OpenGL::Core::VertexBuffer_OpenGL::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}