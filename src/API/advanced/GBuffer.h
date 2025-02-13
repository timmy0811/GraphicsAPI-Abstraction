#pragma once

#include "API/core/Framebuffer.h"

namespace API::Advanced {
	class GBuffer
	{
	public:
		virtual ~GBuffer() = default;

		virtual int GetInternalId() const = 0;

		virtual void Bind() const = 0;
		virtual void BindAndClear() = 0;
		virtual void Unbind() = 0;

		virtual void BindTexture(unsigned int slot, unsigned int index) = 0;
		virtual void BindTexture(const std::string& identifier, unsigned int index) = 0;
		virtual void BindTextures(unsigned int startSlot = 0) = 0;

		virtual unsigned int GetTargetInternalId(const std::string& identifier) = 0;
		virtual unsigned int GetTargetBoundTextureSlot(const std::string& identifier) = 0;
		virtual const std::string GetTargetIdentifier(unsigned int internalId) = 0;

		virtual void BindDepthTexture(unsigned int slot) = 0;

		virtual unsigned int AddRenderTarget(const std::string& identifier, unsigned int width, unsigned int height, unsigned int components, Core::BufferDataType datatype, Core::WrapMethod wrap = Core::WrapMethod::CLAMP_TO_EDGE, void* data = nullptr) = 0;
		virtual unsigned int AddRenderTarget(const std::string& identifier, unsigned int components, Core::BufferDataType datatype, Core::WrapMethod wrap = Core::WrapMethod::CLAMP_TO_EDGE, void* data = nullptr) = 0;

		virtual unsigned int AddDepthTarget(unsigned int width, unsigned int height, Core::DepthBufferType type = Core::DepthBufferType::WRITE_ONLY) = 0;
		virtual unsigned int AddDepthTarget(Core::DepthBufferType type = Core::DepthBufferType::WRITE_ONLY) = 0;

		virtual unsigned int AddStencilTarget(unsigned int width, unsigned int height) = 0;
		virtual unsigned int AddStencilTarget() = 0;

		virtual bool Validate() = 0;

		virtual inline size_t AttachementCount() const = 0;

		static GBuffer* Create(unsigned int width, unsigned int height);
	};
}