#pragma once

#include <vendor/glm/glm.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "PropertyEnums.h"

namespace API::Core {
	class RendererAPI
	{
	public:
		enum class API_ENUM
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void ClearStencilBuffer() = 0;

		virtual void SetDepthTest(bool enabled) = 0;
		virtual void SetDepthTestFunc(DepthFunction func) = 0;
		virtual void SetDepthTestRange(float min, float max) = 0;

		virtual void SetBlend(bool enabled) = 0;
		virtual void SetBlendFunc(BlendFunction source, BlendFunction destination) = 0;

		virtual void CullFace(Face mode) = 0;
		virtual void SetFrontFace(FrontFace face) = 0;
		virtual void SetStencilTest(bool enabled) = 0;
		virtual void EnableAntiAliasing(AntiAliasingMethod method) = 0;

		virtual void EnableStencilTestWithConstant(unsigned int mask) = 0;
		virtual void SetDefaultStencilTest() = 0;
		virtual void CopyStencilBuffer(unsigned int source, unsigned dest, int width, int height) = 0;
		virtual void CopyDepthBuffer(unsigned int source, unsigned dest, int width, int height) = 0;

		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray, size_t size) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, size_t size, unsigned int instances) = 0;
		virtual void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer, unsigned int instances) = 0;

		inline static API_ENUM GetAPI() { return s_API; }

		virtual const std::string GetAPIVer() const = 0;
		virtual const std::string GetGPUID() const = 0;
		virtual const std::string GetPublisher() const = 0;
		virtual const std::string GetShaderLanID() const = 0;

	private:
		static API_ENUM s_API;
	};
}