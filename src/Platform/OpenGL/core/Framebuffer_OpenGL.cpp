#include "glpch.h"
#include "Framebuffer_OpenGL.h"

OpenGL::Core::Framebuffer_OpenGL::Framebuffer_OpenGL(const glm::ivec2& size, const bool attachDepth,
                                                     const API::Core::DepthBufferType depthType):
	m_BoundPort(-1)
{
	m_Width = size.x;
	m_Height = size.y;

	m_Attachments.reserve(MAX_BUF);

	GLCall(glGenFramebuffers(1, &m_IdFBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_IdFBO));

	if (attachDepth)
	{
		switch (depthType)
		{
		case API::Core::DepthBufferType::WRITE_ONLY:
			glGenRenderbuffers(1, &m_RBODepth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_RBODepth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int)m_Width, (int)m_Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_RBODepth);

			break;
		case API::Core::DepthBufferType::WRITE_READ:
			GLCall(glGenTextures(1, &m_RBODepth));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_RBODepth));
			GLCall(
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
					nullptr));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_IdFBO));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_RBODepth, 0));

			GLCall(glDrawBuffer(GL_NONE));
			GLCall(glReadBuffer(GL_NONE));

			break;
		default:
			break;
		}
	}

	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[OpenGL Error] (" << std::to_string(status) << ")" << std::endl;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

OpenGL::Core::Framebuffer_OpenGL::Framebuffer_OpenGL(const glm::ivec2& size): m_BoundPort(-1)
{
	m_Width = size.x;
	m_Height = size.y;

	m_Attachments.reserve(MAX_BUF);

	GLCall(glGenFramebuffers(1, &m_IdFBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_IdFBO));

	m_Attachments.push_back(GL_COLOR_ATTACHMENT0);

	// Color attachment
	glGenTextures(1, &m_Attachments[0]);
	glBindTexture(GL_TEXTURE_2D, m_Attachments[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)m_Width, (int)m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Attachments[0], 0);

	// Depth attachment
	glGenRenderbuffers(1, &m_RBODepth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBODepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)m_Width, (int)m_Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBODepth);

	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[OpenGL Error] (" << std::to_string(status) << ")" << std::endl;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

unsigned int OpenGL::Core::Framebuffer_OpenGL::BindDepthTexture(const unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	// m_RBODepth can be a renderbuffer (WRITE_ONLY) or a texture (WRITE_READ)
	if (glIsTexture(m_RBODepth) == GL_TRUE)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RBODepth));
	}
	else
	{
		// Avoid GL errors by not binding renderbuffers as textures
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		// Optional: log once per frame if needed
		// std::cout << "[GL Warning] Attempted to bind depth renderbuffer as texture; skipped." << std::endl;
	}
	m_BoundPort = static_cast<int>(slot);
	return m_BoundPort;
}

void OpenGL::Core::Framebuffer_OpenGL::Bind(const unsigned int Framebuffer)
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Framebuffer));
}

void OpenGL::Core::Framebuffer_OpenGL::Bind() const
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IdFBO));
	GLCall(glViewport(0, 0, m_Width, m_Height));
}

void OpenGL::Core::Framebuffer_OpenGL::BindAndClear()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_IdFBO));
	GLCall(glViewport(0, 0, m_Width, m_Height));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGL::Core::Framebuffer_OpenGL::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OpenGL::Core::Framebuffer_OpenGL::BindTextures(const unsigned int startSlot)
{
	for (int i = 0; i < m_Buffers.size(); i++)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + startSlot + i));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_Buffers[i]));
	}
}

void OpenGL::Core::Framebuffer_OpenGL::BindTexture(const int index, const unsigned int startSlot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + startSlot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Buffers[index]));
}

bool OpenGL::Core::Framebuffer_OpenGL::PushColorAttribute(const char channel, const API::Core::BufferDataType dataType,
                                                          const void* data)
{
	const TextureFormat format = GetTextureFormat(channel, dataType);

	const size_t size = m_Buffers.size();
	m_Buffers.push_back(0);

	GLCall(glGenTextures(1, &(m_Buffers[size])));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Buffers[size]));
	GLCall(
		glTexImage2D(GL_TEXTURE_2D, 0, format.InternalFormat, m_Width, m_Height, 0, format.Format, format.Type, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (int)size, GL_TEXTURE_2D, m_Buffers[size], 0));

	m_Attachments.push_back(GL_COLOR_ATTACHMENT0 + (int)m_Attachments.size());
	glDrawBuffers((int)m_Attachments.size(), &m_Attachments[0]);

	return true;
}

bool OpenGL::Core::Framebuffer_OpenGL::PushColorAttribute(const unsigned int internalFormat, const unsigned int format,
                                                          const unsigned int dataType, const void* data)
{
	const size_t size = m_Buffers.size();
	m_Buffers.push_back(0);

	GLCall(glGenTextures(1, &(m_Buffers[size])));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Buffers[size]));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, dataType, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (int)size, GL_TEXTURE_2D, m_Buffers[size], 0));

	m_Attachments.push_back(GL_COLOR_ATTACHMENT0 + (int)m_Attachments.size());
	glDrawBuffers((int)m_Attachments.size(), &m_Attachments[0]);

	return true;
}

inline unsigned int OpenGL::Core::Framebuffer_OpenGL::GetColorAttachmentTextureID(const unsigned int index)
{
	return m_Attachments[index];
}

inline bool OpenGL::Core::Framebuffer_OpenGL::Validate() const
{
	Bind();
	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "[OpenGL Error] (" << std::to_string(status) << ")" << std::endl;
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		return false;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return true;
}

OpenGL::Core::Framebuffer_OpenGL::TextureFormat OpenGL::Core::Framebuffer_OpenGL::GetTextureFormat(
	const unsigned int components, const API::Core::BufferDataType datatype)
{
	TextureFormat format{};

	switch (components)
	{
	case 1: format.Format = GL_RED;
		break;
	case 2: format.Format = GL_RG;
		break;
	case 3: format.Format = GL_RGB;
		break;
	case 4: format.Format = GL_RGBA;
		break;
	default:
		LOG_GL_ERROR("Invalid component count: must be 1, 2, 3, or 4.");
		return {};
	}

	switch (datatype)
	{
	case API::Core::BufferDataType::_FLOAT:
		format.InternalFormat = (components == 1)
			                        ? GL_R32F
			                        : (components == 2)
			                        ? GL_RG32F
			                        : (components == 3)
			                        ? GL_RGB32F
			                        : GL_RGBA32F;
		format.Type = GL_FLOAT;
		break;

	case API::Core::BufferDataType::_FLOAT16:
		format.InternalFormat = (components == 1)
			                        ? GL_R16F
			                        : (components == 2)
			                        ? GL_RG16F
			                        : (components == 3)
			                        ? GL_RGB16F
			                        : GL_RGBA16F;
		format.Type = GL_HALF_FLOAT;
		break;

	case API::Core::BufferDataType::_DOUBLE:
		format.InternalFormat = (components == 1)
			                        ? GL_R32F
			                        : (components == 2)
			                        ? GL_RG32F
			                        : (components == 3)
			                        ? GL_RGB32F
			                        : GL_RGBA32F;
		format.Type = GL_DOUBLE;
		break;

	case API::Core::BufferDataType::_BYTE_UNSIGNED:
		format.InternalFormat = (components == 1)
			                        ? GL_R8
			                        : (components == 2)
			                        ? GL_RG8
			                        : (components == 3)
			                        ? GL_RGB8
			                        : GL_RGBA8;
		format.Type = GL_UNSIGNED_BYTE;
		break;

	case API::Core::BufferDataType::_BYTE:
		format.InternalFormat = (components == 1)
			                        ? GL_R8_SNORM
			                        : (components == 2)
			                        ? GL_RG8_SNORM
			                        : (components == 3)
			                        ? GL_RGB8_SNORM
			                        : GL_RGBA8_SNORM;
		format.Type = GL_BYTE;
		break;

	case API::Core::BufferDataType::_SHORT:
		format.InternalFormat = (components == 1)
			                        ? GL_R16_SNORM
			                        : (components == 2)
			                        ? GL_RG16_SNORM
			                        : (components == 3)
			                        ? GL_RGB16_SNORM
			                        : GL_RGBA16_SNORM;
		format.Type = GL_SHORT;
		break;

	case API::Core::BufferDataType::_SHORT_UNSIGNED:
		format.InternalFormat = (components == 1)
			                        ? GL_R16
			                        : (components == 2)
			                        ? GL_RG16
			                        : (components == 3)
			                        ? GL_RGB16
			                        : GL_RGBA16;
		format.Type = GL_UNSIGNED_SHORT;
		break;

	case API::Core::BufferDataType::_INT:
		format.InternalFormat = (components == 1)
			                        ? GL_R32I
			                        : (components == 2)
			                        ? GL_RG32I
			                        : (components == 3)
			                        ? GL_RGB32I
			                        : GL_RGBA32I;
		format.Type = GL_INT;
		break;

	case API::Core::BufferDataType::_INT_UNSIGNED:
		format.InternalFormat = (components == 1)
			                        ? GL_R32UI
			                        : (components == 2)
			                        ? GL_RG32UI
			                        : (components == 3)
			                        ? GL_RGB32UI
			                        : GL_RGBA32UI;
		format.Type = GL_UNSIGNED_INT;
		break;

	case API::Core::BufferDataType::_NONE:
		LOG_GL_ERROR("Invalid BufferDataType: _NONE is not a valid texture data type.");
		break;
	default:
		LOG_GL_ERROR("Unknown BufferDataType.");
	}

	return format;
}
