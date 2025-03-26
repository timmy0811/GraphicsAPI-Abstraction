#pragma once

#include "RendererAPI.h"

namespace API::Core {
	class RenderCommand
	{
	public:
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
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

		inline static void ClearStencilBuffer()
		{
			s_RendererAPI->ClearStencilBuffer();
		}

		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray, size_t size)
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

		inline static void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, size_t size, unsigned int instances)
		{
			s_RendererAPI->DrawInstanced(vertexArray, size, instances);
		}

		inline static void DrawInstanced(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<IndexBuffer>& indexBuffer, unsigned int instances)
		{
			s_RendererAPI->DrawInstanced(vertexArray, indexBuffer, instances);
		}

		inline static void SetDepthTest(bool enabled) {
			s_RendererAPI->SetDepthTest(enabled);
		}

		inline static void SetDepthTestFunc(DepthFunction func) {
			s_RendererAPI->SetDepthTestFunc(func);
		}

		inline static void SetDepthTestRange(float min, float max) {
			s_RendererAPI->SetDepthTestRange(min, max);
		}

		inline static void SetBlend(bool enabled) {
			s_RendererAPI->SetBlend(enabled);
		}

		inline static void SetBlendFunc(BlendFunction source, BlendFunction destination) {
			s_RendererAPI->SetBlendFunc(source, destination);
		}

		inline static void CullFace(Face mode) {
			s_RendererAPI->CullFace(mode);
		}

		inline static void SetFrontFace(FrontFace face) {
			s_RendererAPI->SetFrontFace(face);
		}

		inline static void SetStencilTest(bool enabled) {
			s_RendererAPI->SetStencilTest(enabled);
		}
		inline static void EnableAntiAliasing(AntiAliasingMethod method) {
			s_RendererAPI->EnableAntiAliasing(method);
		}

		inline static void EnableStencilTestWithConstant(unsigned int constant) {
			s_RendererAPI->EnableStencilTestWithConstant(constant);
		}

		inline static void SetDefaultStencilTest() {
			s_RendererAPI->SetDefaultStencilTest();
		}

		inline static void CopyStencilBuffer(unsigned int source, unsigned dest, int width, int height) {
			s_RendererAPI->CopyStencilBuffer(source, dest, width, height);
		}

		inline static void CopyDepthBuffer(unsigned int source, unsigned dest, int width, int height) {
			s_RendererAPI->CopyDepthBuffer(source, dest, width, height);
		}

	public:
		inline static const std::string GetAPIVer() { return s_RendererAPI->GetAPIVer(); }
		inline static const std::string GetGPUID() { return s_RendererAPI->GetGPUID(); }
		inline static const std::string GetPublisher() { return s_RendererAPI->GetPublisher(); }
		inline static const std::string GetShaderLanID() { return s_RendererAPI->GetShaderLanID(); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}