#pragma once

#include "RendererAPI.h"

namespace API::Core
{
	class RenderCommand
	{
	public:
		inline static void SetViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetWireframeMode(const bool enabled)
		{
			s_RendererAPI->SetWireframeMode(enabled);
		}

		inline static void ClearStencilBuffer()
		{
			s_RendererAPI->ClearStencilBuffer();
		}

		inline static void IssueEmptyDrawCall(const int instances)
		{
			s_RendererAPI->IssueEmptyDrawCall(instances);
		}

		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray, const size_t size)
		{
			s_RendererAPI->Draw(vertexArray, size);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexBuffer);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Buffer>& indexBuffer)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexBuffer);
		}

		inline static void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, const size_t size, const unsigned int instances)
		{
			s_RendererAPI->DrawInstanced(vertexArray, size, instances);
		}

		inline static void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer, const unsigned int instances)
		{
			s_RendererAPI->DrawInstanced(vertexArray, indexBuffer, instances);
		}

		inline static void SetDepthTest(const bool enabled)
		{
			s_RendererAPI->SetDepthTest(enabled);
		}

		inline static void SetDepthTestFunc(const DepthFunction func)
		{
			s_RendererAPI->SetDepthTestFunc(func);
		}

		inline static void SetDepthTestRange(const float min, const float max)
		{
			s_RendererAPI->SetDepthTestRange(min, max);
		}

		inline static void SetBlend(const bool enabled)
		{
			s_RendererAPI->SetBlend(enabled);
		}

		inline static void SetBlendFunc(const BlendFunction source, const BlendFunction destination)
		{
			s_RendererAPI->SetBlendFunc(source, destination);
		}

		inline static void CullFace(const Face mode)
		{
			s_RendererAPI->CullFace(mode);
		}

		inline static void SetFrontFace(const FrontFace face)
		{
			s_RendererAPI->SetFrontFace(face);
		}

		inline static void SetStencilTest(const bool enabled)
		{
			s_RendererAPI->SetStencilTest(enabled);
		}

		inline static void EnableAntiAliasing(const AntiAliasingMethod method)
		{
			s_RendererAPI->EnableAntiAliasing(method);
		}

		inline static void EnableStencilTestWithConstant(const unsigned int constant)
		{
			s_RendererAPI->EnableStencilTestWithConstant(constant);
		}

		inline static void SetDefaultStencilTest()
		{
			s_RendererAPI->SetDefaultStencilTest();
		}

		inline static void CopyStencilBuffer(const unsigned int source, const unsigned dest, const int width, const int height)
		{
			s_RendererAPI->CopyStencilBuffer(source, dest, width, height);
		}

		inline static void CopyDepthBuffer(const unsigned int source, const unsigned dest, const int width, const int height)
		{
			s_RendererAPI->CopyDepthBuffer(source, dest, width, height);
		}

		inline static void UnbindAllFramebuffers()
		{
			s_RendererAPI->UnbindAllFramebuffers();
		}

		inline static void UnbindShaderProgram()
		{
			s_RendererAPI->UnbindShaderProgram();
		}

		inline static void UnbindAllTextures(const int maxTextureUnits = 32)
		{
			s_RendererAPI->UnbindAllTextures(maxTextureUnits);
		}

		inline static void UnbindRenderbuffer()
		{
			s_RendererAPI->UnbindRenderbuffer();
		}

		inline static void ForceSync()
		{
			s_RendererAPI->ForceSync();
		}

	public:
		inline static std::string GetAPIVer() { return s_RendererAPI->GetAPIVer(); }
		inline static std::string GetGPUID() { return s_RendererAPI->GetGPUID(); }
		inline static std::string GetPublisher() { return s_RendererAPI->GetPublisher(); }
		inline static std::string GetShaderLanID() { return s_RendererAPI->GetShaderLanID(); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}
