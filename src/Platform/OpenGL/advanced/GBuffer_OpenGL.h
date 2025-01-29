#pragma once

#include "API/Advanced/GBuffer.h"
#include <GL/glew.h>

namespace OpenGL::Advanced {
	class GBuffer_OpenGL : public API::Advanced::GBuffer
	{
	public:
		GBuffer_OpenGL(unsigned int width, unsigned int height);
		~GBuffer_OpenGL() = default;

		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindDepthTexture(unsigned int slot) override;

		void BindTexture(unsigned int slot, unsigned int index) override;
		void BindTexture(const std::string& identifier, unsigned int index) override;
		void BindTextures(unsigned int startSlot = 0) override;

		unsigned int GetTargetInternalId(const std::string& identifier) override;
		const std::string GetTargetIdentifier(unsigned int internalId) override;

		unsigned int AddRenderTarget(const std::string& identifier, unsigned int width, unsigned int height, unsigned int components, API::Core::BufferDataType datatype, API::Core::WrapMethod wrap = API::Core::WrapMethod::CLAMP_TO_EDGE, void* data = nullptr) override;
		unsigned int AddRenderTarget(const std::string& identifier, unsigned int components, API::Core::BufferDataType datatype, API::Core::WrapMethod wrap = API::Core::WrapMethod::CLAMP_TO_EDGE, void* data = nullptr) override;

		unsigned int AddDepthTarget(unsigned int width, unsigned int height, API::Core::DepthBufferType type = API::Core::DepthBufferType::WRITE_ONLY) override;
		unsigned int AddDepthTarget(API::Core::DepthBufferType type = API::Core::DepthBufferType::WRITE_ONLY) override;

		bool Validate() override;

		inline size_t AttachementCount() const override { return Targets.size(); }

	private:
		struct TextureFormat
		{
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		TextureFormat GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype);

	private:
		unsigned int Width, Height;

		unsigned int IdGBuffer;
		std::vector<std::pair<std::string, GLuint>> Targets;
		unsigned int DepthTarget;
	};
}