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

		[[nodiscard]] int GetInternalId() const override { return (int)m_IdFBO; }

		void Bind(unsigned int Framebuffer) override;

		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindTextures(unsigned int startSlot) override;
		void BindTexture(int index, unsigned int startSlot) override;
		unsigned int BindDepthTexture(unsigned int slot) override;

		bool PushColorAttribute(char channel, API::Core::BufferDataType dataType, const void* data) override;
		bool PushColorAttribute(unsigned int internalFormat, unsigned int format, unsigned int dataType, const void* data) override;

		inline unsigned int GetColorAttachmentTextureID(unsigned int index) override;

		[[nodiscard]] inline size_t AttachmentCount() const override { return m_Attachments.size(); }
		inline bool Validate() const override;

	private:
		struct TextureFormat
		{
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		static TextureFormat GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype);

	private:
		unsigned int m_IdFBO{}, m_RBODepth{};
		std::vector<GLuint> m_Buffers;
		std::vector<GLuint> m_Attachments;

		int m_BoundPort;
	};
}
