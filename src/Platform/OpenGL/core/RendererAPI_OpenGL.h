#pragma once

#include "API/core/RendererAPI.h"

namespace OpenGL::Core {
	class RendererAPI_OpenGL : public API::Core::RendererAPI
	{
	public:
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void ClearStencilBuffer() override;

		virtual void Draw(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size) override;
		virtual void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& ib) override;
		virtual void DrawIndexed(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::Buffer>& ib) override;

		virtual void DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, size_t size, unsigned int instances) override;
		virtual void DrawInstanced(const std::shared_ptr<API::Core::VertexArray>& vertexArray, const std::shared_ptr<API::Core::IndexBuffer>& indexBuffer, unsigned int instances) override;

		virtual void SetDepthTest(bool enabled) override;
		virtual void SetDepthTestFunc(API::Core::DepthFunction func) override;
		virtual void SetDepthTestRange(float min, float max) override;

		virtual void SetBlend(bool enabled) override;
		virtual void SetBlendFunc(API::Core::BlendFunction source, API::Core::BlendFunction destination) override;

		virtual void CullFace(API::Core::Face mode) override;
		virtual void SetFrontFace(API::Core::FrontFace face) override;
		virtual void SetStencilTest(bool enabled) override;
		virtual void EnableAntiAliasing(API::Core::AntiAliasingMethod method) override;

		virtual void EnableStencilTestWithConstant(unsigned int mask) override;
		virtual void SetDefaultStencilTest() override;
		virtual void CopyStencilBuffer(unsigned int source, unsigned dest, int width, int height) override;
		virtual void CopyDepthBuffer(unsigned int source, unsigned dest, int width, int height) override;

		virtual const std::string GetAPIVer() const;
		virtual const std::string GetGPUID() const;
		virtual const std::string GetPublisher() const;
		virtual const std::string GetShaderLanID() const;
	};
}