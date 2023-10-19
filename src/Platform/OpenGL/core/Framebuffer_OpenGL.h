#pragma once

#include "vendor/glm/glm.hpp"
#include "Debug/Debug.h"
#include "API/core/Framebuffer.h"

#include <vector>
#include <GLEW/glew.h>

namespace OpenGL::Core {
	class Framebuffer_OpenGL : public API::Core::Framebuffer
	{
	public:
		Framebuffer_OpenGL(const glm::ivec2& size, bool attachDepth = true, DepthBufferType depthType = DepthBufferType::WRITE_ONLY);

		void Bind(unsigned int Framebuffer) override;
		
		void Bind() const override;
		void BindAndClear() override;
		void Unbind() override;

		void BindTextures(const unsigned int startSlot = 0) override;
		void BindTexture(int index, const unsigned int startSlot = 0) override;
		unsigned int BindDepthTexture(const unsigned int slot) override;

		bool PushColorAttribute(const char channel = 3, BufferDataType dataType = BufferDataType::_FLOAT, const void* data = nullptr) override;
		bool PushColorAttribute(unsigned int internalFormat = GL_RGBA16F, unsigned int format = GL_RGBA, unsigned int dataType = GL_FLOAT, const void* data = nullptr) override;

		inline size_t AttachementCount() const override { return m_Attachements.size(); }
		inline bool Validate() const override;

	private:
		unsigned int m_IdFBO, m_RBODepth;
		std::vector<GLuint> m_Buffers;
		std::vector<GLuint> m_Attachements;

		int m_BoundPort;
	};
}