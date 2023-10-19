#include "glpch.h"
#include "LegacyRenderer.h"

#include "Debug/Debug.h"
#include "API/core/Renderer.h"

#include <GLEW/glew.h>

void API::Legacy::LegacyRenderer::Init()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &FramebufferOriginId));
	}
	}
}

void API::Legacy::LegacyRenderer::BindOrigFramebuffer()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferOriginId));
	}
	}
}

void API::Legacy::LegacyRenderer::Clear()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	}
}

void API::Legacy::LegacyRenderer::ClearDepthBufferOnly()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	}
	}
}

void API::Legacy::LegacyRenderer::Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, int mode, int count)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		size_t c = count == -1 ? ib.GetCount() : (size_t)count;
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(mode, (int)c, GL_UNSIGNED_INT, nullptr));
	}
	}
}

void API::Legacy::LegacyRenderer::Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, size_t count)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, (int)count, GL_UNSIGNED_INT, nullptr));
	}
	}
}

void API::Legacy::LegacyRenderer::DrawArray(const Core::VertexArray& va, const Core::Shader& shader, size_t first, size_t count)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		glDrawArrays(GL_TRIANGLES, (int)first, (int)count);
	}
	}
}

void API::Legacy::LegacyRenderer::DrawInstancedLines(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, size_t count, size_t instances)
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case API::Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElementsInstanced(GL_LINES, (int)count, GL_UNSIGNED_INT, nullptr, (int)instances));
	}
	}
}