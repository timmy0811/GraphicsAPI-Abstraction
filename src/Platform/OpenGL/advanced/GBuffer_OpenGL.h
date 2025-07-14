#pragma once

#include "API/advanced/GBuffer.h"
#include <GL/glew.h>

namespace OpenGL::Advanced
{
	class GBuffer_OpenGL final : public API::Advanced::GBuffer
	{
	public:
		GBuffer_OpenGL(unsigned int width, unsigned int height);
		~GBuffer_OpenGL() override = default;

		[[nodiscard]] int GetInternalId() const override { return (int)IdGBuffer; }

		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindDepthTexture(unsigned int slot) override;

		void BindTexture(unsigned int slot, unsigned int index) override;
		void BindTexture(const std::string& identifier, unsigned int index) override;
		void BindTextures(unsigned int startSlot) override;

		unsigned int GetTargetInternalId(const std::string& identifier) override;
		unsigned int GetTargetBoundTextureSlot(const std::string& identifier) override;
		std::string GetTargetIdentifier(unsigned int internalId) override;

		unsigned int AddRenderTarget(const std::string& identifier, unsigned int width, unsigned int height,
		                             unsigned int components, API::Core::BufferDataType datatype,
		                             API::Core::WrapMethod wrap, void* data) override;
		unsigned int AddRenderTarget(const std::string& identifier, unsigned int components,
		                             API::Core::BufferDataType datatype,
		                             API::Core::WrapMethod wrap, void* data = nullptr) override;

		unsigned int AddDepthTarget(unsigned int width, unsigned int height, API::Core::DepthBufferType type) override;
		unsigned int AddDepthTarget(API::Core::DepthBufferType type) override;

		unsigned int AddStencilTarget(unsigned int width, unsigned int height) override;
		unsigned int AddStencilTarget() override;

		bool Validate() override;

		[[nodiscard]] inline size_t AttachmentCount() const override { return Targets.size(); }

	private:
		struct TextureFormat
		{
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		static TextureFormat GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype);
		static inline int GetBoundFBO();

	private:
		struct InternalTargetData
		{
			bool IsBound;
			unsigned int BoundSlot;
			GLuint InternalId;
		};

		unsigned int Width, Height;

		unsigned int IdGBuffer = 0;
		std::vector<std::pair<std::string, InternalTargetData>> Targets;
		unsigned int DepthTarget = 0;
		unsigned int StencilTarget = 0;
	};
}
