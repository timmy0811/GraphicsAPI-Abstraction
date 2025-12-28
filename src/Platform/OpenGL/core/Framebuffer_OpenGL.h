#pragma once

#include "vendor/glm/glm.hpp"
#include "Debug/Debug.h"
#include "API/core/Framebuffer.h"

#include <vector>
#include <GL/glew.h>

namespace OpenGL::Core
{
	class Framebuffer_OpenGL final : public API::Core::Framebuffer
	{
	public:
		Framebuffer_OpenGL(const glm::ivec2& size, bool attachDepth,
		                   API::Core::DepthBufferType depthType = API::Core::DepthBufferType::WRITE_ONLY);

		explicit Framebuffer_OpenGL(const glm::ivec2& size);

		~Framebuffer_OpenGL() override;

		// Non-copyable
		Framebuffer_OpenGL(const Framebuffer_OpenGL&) = delete;
		Framebuffer_OpenGL& operator=(const Framebuffer_OpenGL&) = delete;

		[[nodiscard]] int GetInternalId() const override { return static_cast<int>(m_FBO); }

		void Bind(unsigned int framebufferId) override;
		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindTextures(unsigned int startSlot) override;
		void BindTexture(int index, unsigned int startSlot) override;
		unsigned int BindDepthTexture(unsigned int slot) override;

		bool PushColorAttribute(char channel, API::Core::BufferDataType dataType, const void* data) override;
		bool PushColorAttribute(unsigned int internalFormat, unsigned int format, unsigned int dataType, const void* data) override;

		unsigned int GetColorAttachmentTextureID(unsigned int index) override;

		// Set the texture filter mode for a color attachment
		void SetColorAttachmentFilter(unsigned int index, unsigned int filter) override;

		[[nodiscard]] size_t AttachmentCount() const override { return m_ColorAttachments.size(); }
		bool Validate() const override;

		// Resize framebuffer in-place
		void Resize(const glm::ivec2& size) override;

	private:
		struct TextureFormat
		{
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		struct ColorAttachmentInfo
		{
			GLuint TextureID;
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		static TextureFormat GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype);
		void UpdateDrawBuffers() const;

	private:
		GLuint m_FBO = 0;

		std::vector<ColorAttachmentInfo> m_ColorAttachments;

		// Draw buffer enum values for glDrawBuffers (GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, etc.)
		std::vector<GLenum> m_DrawBuffers;

		// Depth/stencil attachment
		GLuint m_DepthAttachment = 0;
		bool m_DepthIsTexture = false;      // true if depth is a texture, false if renderbuffer
		bool m_HasDepthStencil = false;     // true if using combined depth-stencil format

		int m_BoundTextureSlot = -1;
	};
}

