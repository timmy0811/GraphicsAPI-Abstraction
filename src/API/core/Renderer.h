#pragma once

#include "RendererCommand.h"

namespace API::Core {

	// This class can be seen as a template clas for RendererContexts that can be implemented in the user application
	// if it is nessecary.

	class DefaultRendererContext {
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
