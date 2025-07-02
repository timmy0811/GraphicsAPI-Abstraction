#include "glpch.h"
#include "Renderer.h"

void API::Core::DefaultRendererContext::BeginScene()
{
}

void API::Core::DefaultRendererContext::EndScene()
{
}

void API::Core::DefaultRendererContext::SubmitDraw(const std::shared_ptr<VertexArray>& va, const size_t size)
{
	va->Bind();
	RenderCommand::Draw(va, size);
}

void API::Core::DefaultRendererContext::SubmitDraw(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib)
{
	va->Bind();
	ib->Bind();
	RenderCommand::DrawIndexed(va, ib);
}

void API::Core::DefaultRendererContext::SubmitInstancedDraw(const std::shared_ptr<VertexArray>& va, const size_t size, const unsigned int instances)
{
	va->Bind();
	RenderCommand::DrawInstanced(va, size, instances);
}

void API::Core::DefaultRendererContext::SubmitInstancedDraw(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib, const unsigned int instances)
{
	va->Bind();
	ib->Bind();
	RenderCommand::DrawInstanced(va, ib, instances);
}