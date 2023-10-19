#pragma once

#include "RendererCommand.h"

namespace API::Core {
	class RendererContext {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& va);
		static void Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<IndexBuffer>& ib);

		inline static RendererAPI::API_ENUM GetAPI() { return RendererAPI::GetAPI(); }

	public:
		static inline int FramebufferOriginId;
	};
}
