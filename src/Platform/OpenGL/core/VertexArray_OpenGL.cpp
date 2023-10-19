#include "glpch.h"
#include "VertexArray_OpenGL.h"

#include <GLEW/glew.h>

OpenGL::Core::VertexArray_OpenGL::VertexArray_OpenGL()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	//GLCall(glBindVertexArray(m_RendererID));
}

OpenGL::Core::VertexArray_OpenGL::~VertexArray_OpenGL()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void OpenGL::Core::VertexArray_OpenGL::AddBuffer(const API::Core::VertexBuffer& vb, const API::Core::VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
#pragma warning(push)
#pragma warning(disable:4312)
		GLCall(glVertexAttribPointer(i, element.components, API::Core::VertexBufferElement::GetAPIDataType(element.type), element.normalized, layout.GetStride(), (const void*)offset));
#pragma warning(pop)
		offset += element.components * API::Core::VertexBufferLayout::ShaderDataTypeSize(element.type);
	}
}

void OpenGL::Core::VertexArray_OpenGL::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void OpenGL::Core::VertexArray_OpenGL::Unbind() const
{
	GLCall(glBindVertexArray(0));
}