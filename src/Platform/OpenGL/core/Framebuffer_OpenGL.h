#pragma once

#include "vendor/glm/glm.hpp"
#include "Debug/Debug.h"
#include "API/core/Framebuffer.h"

#include <vector>
#include <GL/glew.h>

namespace OpenGL::Core {
	class Framebuffer_OpenGL : public API::Core::Framebuffer
	{
	public:
		Framebuffer_OpenGL(const glm::ivec2& size, bool attachDepth, API::Core::DepthBufferType depthType = API::Core::DepthBufferType::WRITE_ONLY);
		Framebuffer_OpenGL(const glm::ivec2& size);

		void Bind(unsigned int Framebuffer) override;

		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindTextures(const unsigned int startSlot = 0) override;
		void BindTexture(int index, const unsigned int startSlot = 0) override;
		unsigned int BindDepthTexture(const unsigned int slot) override;

		bool PushColorAttribute(const char channel = 3, API::Core::BufferDataType dataType = API::Core::BufferDataType::_FLOAT, const void* data = nullptr) override;
		bool PushColorAttribute(unsigned int internalFormat = GL_RGBA16F, unsigned int format = GL_RGBA, unsigned int dataType = GL_FLOAT, const void* data = nullptr) override;

		virtual inline unsigned int GetColorAttachmentTextureID(unsigned int index) override;

		inline size_t AttachementCount() const override { return m_Attachements.size(); }
		inline bool Validate() const override;

	private:
		struct TextureFormat
		{
			GLint InternalFormat;
			GLenum Format;
			GLenum Type;
		};

		TextureFormat GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype);

	private:
		unsigned int m_IdFBO, m_RBODepth;
		std::vector<GLuint> m_Buffers;
		std::vector<GLuint> m_Attachements;

		int m_BoundPort;
	};
}