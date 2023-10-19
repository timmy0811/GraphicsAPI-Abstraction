#include "glpch.h"
#include "Renderer.h"

void API::Core::RendererContext::BeginScene()
{
}

void API::Core::RendererContext::EndScene()
{
}

void API::Core::RendererContext::Submit(const std::shared_ptr<VertexArray>& va)
{
	va->Bind();
	RenderCommand::DrawIndexed(va);
}

void API::Core::RendererContext::Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib)
{
	va->Bind();
	ib->Bind();
	RenderCommand::DrawIndexed(va, ib);
}