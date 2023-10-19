#include "glpch.h"
#include "IndexBuffer_OpenGL.h"

#include "Debug/Debug.h"

#include <GLEW/glew.h>

OpenGL::Core::IndexBuffer_OpenGL::IndexBuffer_OpenGL(const unsigned int* data, unsigned int count)
{
	m_Count = count;
	API_ASSERT(sizeof(unsigned int) == sizeof(GLuint), "Mismatch in OpenGL datatype size!");

	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

OpenGL::Core::IndexBuffer_OpenGL::~IndexBuffer_OpenGL()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void OpenGL::Core::IndexBuffer_OpenGL::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void OpenGL::Core::IndexBuffer_OpenGL::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int OpenGL::Core::IndexBuffer_OpenGL::GetCount() const
{
	return m_Count;
}