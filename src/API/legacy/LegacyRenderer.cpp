#include "glpch.h"
#include "LegacyRenderer.h"

#include "Debug/Debug.h"
#include "API/core/Renderer.h"

#include <GL/glew.h>

void API::Legacy::LegacyRenderer::Init()
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &FramebufferOriginId));
	}
	}
}

void API::Legacy::LegacyRenderer::BindOrigFramebuffer()
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FramebufferOriginId));
	}
	}
}

void API::Legacy::LegacyRenderer::Clear()
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}
	}
}

void API::Legacy::LegacyRenderer::ClearDepthBufferOnly()
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	}
	}
}

void API::Legacy::LegacyRenderer::Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, const int mode, const int count)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		const size_t c = count == -1 ? ib.GetCount() : (size_t)count;
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(mode, (int)c, GL_UNSIGNED_INT, nullptr));
	}
	}
}

void API::Legacy::LegacyRenderer::Draw(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, const size_t count)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, (int)count, GL_UNSIGNED_INT, nullptr));
	}
	}
}

void API::Legacy::LegacyRenderer::DrawArray(const Core::VertexArray& va, const Core::Shader& shader, const size_t first, const size_t count)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		glDrawArrays(GL_TRIANGLES, (int)first, (int)count);
	}
	}
}

void API::Legacy::LegacyRenderer::DrawInstancedLines(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader, const size_t count, const size_t instances)
{
	switch (Core::DefaultRendererContext::GetAPI())
	{
	case Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); break;
	case Core::RendererAPI::API_ENUM::OpenGL: {
		shader.Bind();
		va.Bind();
		ib.Bind();
		GLCall(glDrawElementsInstanced(GL_LINES, (int)count, GL_UNSIGNED_INT, nullptr, (int)instances));
	}
	}
}