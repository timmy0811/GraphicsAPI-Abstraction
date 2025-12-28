#pragma once

#include "API/core/RendererAPI.h"

namespace OpenGL::Core
{
	class RendererAPI_OpenGL final : public API::Core::RendererAPI
	{
	public:
		void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void ClearStencilBuffer() override;

		void IssueEmptyDrawCall(int instances) override;
		void Draw(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size) override;
		void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer) override;
		void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::Buffer>& indexBuffer) override;

		void DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size, unsigned int instances) override;
		void DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer, unsigned int instances) override;

		void UnbindAllFramebuffers() override;
		void UnbindShaderProgram() override;
		void UnbindAllTextures(int maxTextureUnits = 32) override;
		void UnbindRenderbuffer() override;
		void ForceSync() override;

		void SetDepthTest(bool enabled) override;
		void SetDepthTestFunc(API::Core::DepthFunction func) override;
		void SetDepthTestRange(float min, float max) override;
		void SetWireframeMode(bool enabled) override;

		void SetBlend(bool enabled) override;
		void SetBlendFunc(API::Core::BlendFunction source, API::Core::BlendFunction destination) override;

		void CullFace(API::Core::Face mode) override;
		void SetFrontFace(API::Core::FrontFace face) override;
		void SetStencilTest(bool enabled) override;
		void EnableAntiAliasing(API::Core::AntiAliasingMethod method) override;

		void EnableStencilTestWithConstant(unsigned int mask) override;
		void SetDefaultStencilTest() override;
		void CopyStencilBuffer(unsigned int source, unsigned dest, int width, int height) override;
		void CopyDepthBuffer(unsigned int source, unsigned dest, int width, int height) override;

		[[nodiscard]] std::string GetAPIVer() const override;
		[[nodiscard]] std::string GetGPUID() const override;
		[[nodiscard]] std::string GetPublisher() const override;
		[[nodiscard]] std::string GetShaderLanID() const override;
	};
}
