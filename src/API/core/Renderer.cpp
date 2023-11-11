#include "glpch.h"
#include "Renderer.h"

void API::Core::DefaultRendererContext::BeginScene()
{
}

void API::Core::DefaultRendererContext::EndScene()
{
}

void API::Core::DefaultRendererContext::Submit(const std::shared_ptr<VertexArray>& va)
{
	va->Bind();
	RenderCommand::DrawIndexed(va);
}

void API::Core::DefaultRendererContext::Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib)
{
	va->Bind();
	ib->Bind();
	RenderCommand::DrawIndexed(va, ib);
}