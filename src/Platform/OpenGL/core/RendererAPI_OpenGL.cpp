#include "glpch.h"
#include "RendererAPI_OpenGL.h"

#include "Platform/OpenGL/core/PropertyEnumMapper.h"

#include <GL/glew.h>

void OpenGL::Core::RendererAPI_OpenGL::SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
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

void OpenGL::Core::RendererAPI_OpenGL::IssueEmptyDrawCall(const int instances)
{
	static bool initialized = false;
	static GLuint emptyVAO;

	if (!initialized)
		GLCall(glGenVertexArrays(1, &emptyVAO));

	GLCall(glBindVertexArray(emptyVAO));

	GLCall(glDrawArrays(GL_TRIANGLES, 0, instances));

	GLCall(glBindVertexArray(0));
}

void OpenGL::Core::RendererAPI_OpenGL::Draw(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const size_t size)
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

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const size_t size, const unsigned int instances)
{
	vertexArray->Bind();
	GLCall(glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)size, instances));
}

void OpenGL::Core::RendererAPI_OpenGL::DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer,
                                                     const unsigned int instances)
{
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr, instances));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTest(const bool enabled)
{
	GLCall(enabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTestFunc(const API::Core::DepthFunction func)
{
	GLCall(glDepthFunc(GLDepthFunction(func)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDepthTestRange(const float min, const float max)
{
	GLCall(glDepthRange(min, max));
}

void OpenGL::Core::RendererAPI_OpenGL::SetWireframeMode(const bool enabled)
{
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL));

	glLineWidth(4.0f);
}

void OpenGL::Core::RendererAPI_OpenGL::SetBlend(const bool enabled)
{
	GLCall(enabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND));
}

void OpenGL::Core::RendererAPI_OpenGL::SetBlendFunc(const API::Core::BlendFunction source, const API::Core::BlendFunction destination)
{
	GLCall(glBlendFunc(GLBlendFunction(source), GLBlendFunction(destination)));
}

void OpenGL::Core::RendererAPI_OpenGL::CullFace(const API::Core::Face mode)
{
	if (mode == API::Core::Face::None)
	{
		GLCall(glDisable(GL_CULL_FACE));
		return;
	}

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GLFaceCull(mode)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetFrontFace(const API::Core::FrontFace face)
{
	GLCall(glFrontFace(GLFrontFace(face)));
}

void OpenGL::Core::RendererAPI_OpenGL::SetStencilTest(const bool enabled)
{
	GLCall(enabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST));
}

void OpenGL::Core::RendererAPI_OpenGL::EnableAntiAliasing(const API::Core::AntiAliasingMethod method)
{
	GLCall(glEnable(GLAntiAliasingMethod(method)));
	if (method == API::Core::AntiAliasingMethod::None)
	{
		GLCall(glDisable(GL_MULTISAMPLE));
	}
}

void OpenGL::Core::RendererAPI_OpenGL::EnableStencilTestWithConstant(const unsigned int mask)
{
	GLCall(glEnable(GL_STENCIL_TEST));
	GLCall(glStencilFunc(GL_ALWAYS, 1, mask));
	GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
}

void OpenGL::Core::RendererAPI_OpenGL::SetDefaultStencilTest()
{
	GLCall(glStencilFunc(GL_EQUAL, 1, 0xFF));
	GLCall(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
}

void OpenGL::Core::RendererAPI_OpenGL::CopyStencilBuffer(const unsigned int source, const unsigned dest, const int width, const int height)
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, source));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest));

	GLCall(glBlitFramebuffer(0, 0, width, height,
	                  0, 0, width, height,
	                  GL_STENCIL_BUFFER_BIT,
	                  GL_NEAREST));

	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

void OpenGL::Core::RendererAPI_OpenGL::CopyDepthBuffer(const unsigned int source, const unsigned dest, const int width, const int height)
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, source));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest));

	GLCall(glBlitFramebuffer(0, 0, width, height,
	                  0, 0, width, height,
	                  GL_DEPTH_BUFFER_BIT,
	                  GL_NEAREST));

	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

std::string OpenGL::Core::RendererAPI_OpenGL::GetAPIVer() const
{
	return std::string((const char*)glGetString(GL_VERSION));
}

std::string OpenGL::Core::RendererAPI_OpenGL::GetGPUID() const
{
	return std::string((const char*)glGetString(GL_RENDERER));
}

std::string OpenGL::Core::RendererAPI_OpenGL::GetPublisher() const
{
	return std::string((const char*)glGetString(GL_VENDOR));
}

std::string OpenGL::Core::RendererAPI_OpenGL::GetShaderLanID() const
{
	return std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
