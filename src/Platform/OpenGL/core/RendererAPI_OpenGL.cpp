#include "glpch.h"
#include "RendererAPI_OpenGL.h"

#include <GL/glew.h>

void OpenGL::Core::RendererAPI_OpenGL::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	GLCall(glViewport(x, y, width, height));
}

void OpenGL::Core::RendererAPI_OpenGL::SetClearColor(const glm::vec4& color)
{
	GLCall(glClearColor(color.r, color.g, color.b, color.a));
}

void OpenGL::Core::RendererAPI_OpenGL::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGL::Core::RendererAPI_OpenGL::Draw(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size)
{
	GLCall(glDrawArrays(GL_TRIANGLES, 0, (GLsizei)size));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer)
{
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size, unsigned int instances)
{
	GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)size, instances));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer, unsigned int instances)
{
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr, instances));
}

const std::string OpenGL::Core::RendererAPI_OpenGL::GetAPIVer() const
{
	return std::string((const char*)glGetString(GL_VERSION));
}

const std::string OpenGL::Core::RendererAPI_OpenGL::GetGPUID() const
{
	return std::string((const char*)glGetString(GL_RENDERER));
}

const std::string OpenGL::Core::RendererAPI_OpenGL::GetPublisher() const
{
	return std::string((const char*)glGetString(GL_VENDOR));
}

const std::string OpenGL::Core::RendererAPI_OpenGL::GetShaderLanID() const
{
	return std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}