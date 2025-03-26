#include "glpch.h"
#include "RendererAPI_OpenGL.h"

#include "Platform/OpenGL/core/PropertyEnumMapper.h"

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

void OpenGL::Core::RendererAPI_OpenGL::ClearStencilBuffer()
{
	GLCall(glClear(GL_STENCIL_BUFFER_BIT));
}

void OpenGL::Core::RendererAPI_OpenGL::Draw(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size)
{
	GLCall(glDrawArrays(GL_TRIANGLES, 0, (GLsizei)size));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer)
{
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::Buffer>& indexBuffer)
{
	GLCall(glDrawElements(GL_TRIANGLES, indexBuffer->GetSize() / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size, unsigned int instances)
{
	vertexArray->Bind();
	GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)size, instances));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer, unsigned int instances)
{
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr, instances));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTest(bool enabled)
{
	GLCall(enabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTestFunc(API::Core::DepthFunction func)
{
	GLCall(glDepthFunc(GLDepthFunction(func)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTestRange(float min, float max)
{
	GLCall(glDepthRange(min, max));
}

void OpenGL::Core::RendererAPI_OpenGL::SetBlend(bool enabled)
{
	GLCall(enabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND));
}

void OpenGL::Core::RendererAPI_OpenGL::SetBlendFunc(API::Core::BlendFunction source, API::Core::BlendFunction destination)
{
	GLCall(glBlendFunc(GLBlendFunction(source), GLBlendFunction(destination)));
}

void OpenGL::Core::RendererAPI_OpenGL::CullFace(API::Core::Face mode)
{
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GLFaceCull(mode)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetFrontFace(API::Core::FrontFace face)
{
	GLCall(glFrontFace(GLFrontFace(face)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetStencilTest(bool enabled)
{
	GLCall(enabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST));
}

void OpenGL::Core::RendererAPI_OpenGL::EnableAntiAliasing(API::Core::AntiAliasingMethod method)
{
	GLCall(glEnable(GLAntiAliasingMethod(method)));
	if (method == API::Core::AntiAliasingMethod::None) {
		GLCall(glDisable(GL_MULTISAMPLE));
	}
}

void OpenGL::Core::RendererAPI_OpenGL::EnableStencilTestWithConstant(unsigned int mask)
{
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, mask);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void OpenGL::Core::RendererAPI_OpenGL::SetDefaultStencilTest()
{
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}

void OpenGL::Core::RendererAPI_OpenGL::CopyStencilBuffer(unsigned int source, unsigned dest, int width, int height)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, source);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest);

	glBlitFramebuffer(0, 0, width, height,
		0, 0, width, height,
		GL_STENCIL_BUFFER_BIT,
		GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void OpenGL::Core::RendererAPI_OpenGL::CopyDepthBuffer(unsigned int source, unsigned dest, int width, int height)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, source);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest);

	glBlitFramebuffer(0, 0, width, height,
		0, 0, width, height,
		GL_DEPTH_BUFFER_BIT,
		GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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