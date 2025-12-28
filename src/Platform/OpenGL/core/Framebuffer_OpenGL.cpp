#include "glpch.h"
#include "Framebuffer_OpenGL.h"

// Constructor: Framebuffer with optional depth attachment
// Use this when you want to add color attachments via PushColorAttribute()
OpenGL::Core::Framebuffer_OpenGL::Framebuffer_OpenGL(const glm::ivec2& size, const bool attachDepth,
                                                     const API::Core::DepthBufferType depthType)
	: m_BoundTextureSlot(-1)
{
	m_Width = size.x;
	m_Height = size.y;

	m_ColorAttachments.reserve(MAX_BUF);
	m_DrawBuffers.reserve(MAX_BUF);

	GLCall(glGenFramebuffers(1, &m_FBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	if (attachDepth)
	{
		switch (depthType)
		{
		case API::Core::DepthBufferType::WRITE_ONLY:
			// Create depth renderbuffer
			GLCall(glGenRenderbuffers(1, &m_DepthAttachment));
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment));
			GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width, m_Height));
			GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment));

			// Unbind
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
			m_DepthIsTexture = false;
			break;

		case API::Core::DepthBufferType::WRITE_READ:
			// Create depth texture
			GLCall(glGenTextures(1, &m_DepthAttachment));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_Width, m_Height, 0,
			                    GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
			GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0));

			// Unbind
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			m_DepthIsTexture = true;

			// For depth-only framebuffers, disable color read/write
			GLCall(glDrawBuffer(GL_NONE));
			GLCall(glReadBuffer(GL_NONE));
			break;
		}
	}

	// Note: We don't validate here because color attachments may be added later via PushColorAttribute()
	// The caller should call Validate() after adding all attachments

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

// Convenience Constructor: Simple framebuffer with RGBA8 color + depth-stencil
OpenGL::Core::Framebuffer_OpenGL::Framebuffer_OpenGL(const glm::ivec2& size)
	: m_BoundTextureSlot(-1)
{
	m_Width = size.x;
	m_Height = size.y;

	m_ColorAttachments.reserve(MAX_BUF);
	m_DrawBuffers.reserve(MAX_BUF);

	GLCall(glGenFramebuffers(1, &m_FBO));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	// Color texture attachment
	ColorAttachmentInfo colorInfo{};
	colorInfo.InternalFormat = GL_RGBA8;
	colorInfo.Format = GL_RGBA;
	colorInfo.Type = GL_UNSIGNED_BYTE;

	GLCall(glGenTextures(1, &colorInfo.TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, colorInfo.TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, colorInfo.InternalFormat, m_Width, m_Height, 0,
	                    colorInfo.Format, colorInfo.Type, nullptr));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorInfo.TextureID, 0));

	m_ColorAttachments.push_back(colorInfo);
	m_DrawBuffers.push_back(GL_COLOR_ATTACHMENT0);

	// Unbind
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	// Create depth-stencil renderbuffer
	GLCall(glGenRenderbuffers(1, &m_DepthAttachment));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment));
	m_DepthIsTexture = false;
	m_HasDepthStencil = true;

	// Unbind
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));

	// Set draw buffers
	GLCall(glDrawBuffers(static_cast<GLsizei>(m_DrawBuffers.size()), m_DrawBuffers.data()));

	// Validate
	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_GL_ERROR("Framebuffer incomplete during creation. Status: ", std::to_string(status));
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

OpenGL::Core::Framebuffer_OpenGL::~Framebuffer_OpenGL()
{
	// Check if this framebuffer is currently bound and unbind
	GLint currentFBO = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);
	if (static_cast<GLuint>(currentFBO) == m_FBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Delete color attachments
	for (const auto& attachment : m_ColorAttachments)
	{
		if (attachment.TextureID != 0)
		{
			GLCall(glDeleteTextures(1, &attachment.TextureID));
		}
	}
	m_ColorAttachments.clear();

	// Delete depth attachment
	if (m_DepthAttachment != 0)
	{
		if (m_DepthIsTexture)
		{
			GLCall(glDeleteTextures(1, &m_DepthAttachment));
		}
		else
		{
			GLCall(glDeleteRenderbuffers(1, &m_DepthAttachment));
		}
		m_DepthAttachment = 0;
	}

	// Delete framebuffer
	if (m_FBO != 0)
	{
		GLCall(glDeleteFramebuffers(1, &m_FBO));
		m_FBO = 0;
	}

	m_DrawBuffers.clear();
}

// Resize - resizes textures in-place without deleting/recreating them
// This prevents texture ID recycling issues
void OpenGL::Core::Framebuffer_OpenGL::Resize(const glm::ivec2& size)
{
	if (size.x == static_cast<int>(m_Width) && size.y == static_cast<int>(m_Height))
	{
		return;
	}

	m_Width = size.x;
	m_Height = size.y;

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	// Resize color attachments in-place
	for (size_t i = 0; i < m_ColorAttachments.size(); ++i)
	{
		auto& attachment = m_ColorAttachments[i];
		GLCall(glBindTexture(GL_TEXTURE_2D, attachment.TextureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, attachment.InternalFormat, m_Width, m_Height, 0,
		                    attachment.Format, attachment.Type, nullptr));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i),
		                              GL_TEXTURE_2D, attachment.TextureID, 0));
	}

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	// Resize depth attachment
	if (m_DepthAttachment != 0)
	{
		if (m_DepthIsTexture)
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
			if (m_HasDepthStencil)
			{
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0,
				                    GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
			}
			else
			{
				GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_Width, m_Height, 0,
				                    GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
			}
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
		else
		{
			// Renderbuffer
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment));
			if (m_HasDepthStencil)
			{
				GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
			}
			else
			{
				GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_Width, m_Height));
			}
			GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		}
	}

	// Re-set draw buffers
	if (!m_DrawBuffers.empty())
	{
		GLCall(glDrawBuffers(static_cast<GLsizei>(m_DrawBuffers.size()), m_DrawBuffers.data()));
	}

	// Validate
	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_GL_ERROR("Framebuffer incomplete after resize. Status: ", std::to_string(status));
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OpenGL::Core::Framebuffer_OpenGL::Bind(const unsigned int framebufferId)
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebufferId));
}

void OpenGL::Core::Framebuffer_OpenGL::Bind() const
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO));
	GLCall(glViewport(0, 0, m_Width, m_Height));
}

void OpenGL::Core::Framebuffer_OpenGL::BindAndClear()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FBO));
	GLCall(glViewport(0, 0, m_Width, m_Height));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void OpenGL::Core::Framebuffer_OpenGL::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OpenGL::Core::Framebuffer_OpenGL::BindTextures(const unsigned int startSlot)
{
	for (size_t i = 0; i < m_ColorAttachments.size(); i++)
	{
		const unsigned int slot = startSlot + static_cast<unsigned int>(i);
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[i].TextureID));
	}
}

void OpenGL::Core::Framebuffer_OpenGL::BindTexture(const int index, const unsigned int startSlot)
{
	if (index < 0 || static_cast<size_t>(index) >= m_ColorAttachments.size())
	{
		LOG_GL_ERROR("BindTexture: Invalid index ", std::to_string(index));
		return;
	}

	GLCall(glActiveTexture(GL_TEXTURE0 + startSlot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[index].TextureID));
}

unsigned int OpenGL::Core::Framebuffer_OpenGL::BindDepthTexture(const unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));

	if (m_DepthAttachment != 0 && m_DepthIsTexture)
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, m_DepthAttachment));
		m_BoundTextureSlot = static_cast<int>(slot);
	}
	else
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		m_BoundTextureSlot = -1;
	}

	return m_BoundTextureSlot;
}

bool OpenGL::Core::Framebuffer_OpenGL::PushColorAttribute(const char channel, const API::Core::BufferDataType dataType,
                                                          const void* data)
{
	const TextureFormat format = GetTextureFormat(static_cast<unsigned int>(channel), dataType);
	if (format.InternalFormat == 0)
	{
		return false;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	const size_t attachmentIndex = m_ColorAttachments.size();

	ColorAttachmentInfo colorInfo{};
	colorInfo.InternalFormat = format.InternalFormat;
	colorInfo.Format = format.Format;
	colorInfo.Type = format.Type;

	GLCall(glGenTextures(1, &colorInfo.TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, colorInfo.TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format.InternalFormat, m_Width, m_Height, 0,
	                    format.Format, format.Type, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(attachmentIndex),
	                              GL_TEXTURE_2D, colorInfo.TextureID, 0));

	m_ColorAttachments.push_back(colorInfo);
	m_DrawBuffers.push_back(GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(attachmentIndex));

	UpdateDrawBuffers();

	// Unbind
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return true;
}

bool OpenGL::Core::Framebuffer_OpenGL::PushColorAttribute(const unsigned int internalFormat, const unsigned int format,
                                                          const unsigned int dataType, const void* data)
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	const size_t attachmentIndex = m_ColorAttachments.size();

	ColorAttachmentInfo colorInfo{};
	colorInfo.InternalFormat = static_cast<GLint>(internalFormat);
	colorInfo.Format = format;
	colorInfo.Type = dataType;

	GLCall(glGenTextures(1, &colorInfo.TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, colorInfo.TextureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, dataType, data));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(attachmentIndex),
	                              GL_TEXTURE_2D, colorInfo.TextureID, 0));

	m_ColorAttachments.push_back(colorInfo);
	m_DrawBuffers.push_back(GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(attachmentIndex));

	UpdateDrawBuffers();

	// Unbind
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return true;
}

unsigned int OpenGL::Core::Framebuffer_OpenGL::GetColorAttachmentTextureID(const unsigned int index)
{
	if (index >= m_ColorAttachments.size())
	{
		LOG_GL_ERROR("GetColorAttachmentTextureID: Invalid index ", std::to_string(index));
		return 0;
	}
	return m_ColorAttachments[index].TextureID;
}

void OpenGL::Core::Framebuffer_OpenGL::SetColorAttachmentFilter(const unsigned int index, const unsigned int filter)
{
	if (index >= m_ColorAttachments.size())
	{
		LOG_GL_ERROR("SetColorAttachmentFilter: Invalid index ", std::to_string(index));
		return;
	}

	GLCall(glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[index].TextureID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

bool OpenGL::Core::Framebuffer_OpenGL::Validate() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_FBO));

	const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_GL_ERROR("Framebuffer validation failed. Status: ", std::to_string(status));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		return false;
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return true;
}

void OpenGL::Core::Framebuffer_OpenGL::UpdateDrawBuffers() const
{
	if (!m_DrawBuffers.empty())
	{
		GLCall(glDrawBuffers(static_cast<GLsizei>(m_DrawBuffers.size()), m_DrawBuffers.data()));
	}
}

OpenGL::Core::Framebuffer_OpenGL::TextureFormat OpenGL::Core::Framebuffer_OpenGL::GetTextureFormat(
	const unsigned int components, const API::Core::BufferDataType datatype)
{
	TextureFormat format{};

	switch (components)
	{
	case 1: format.Format = GL_RED; break;
	case 2: format.Format = GL_RG; break;
	case 3: format.Format = GL_RGB; break;
	case 4: format.Format = GL_RGBA; break;
	default:
		LOG_GL_ERROR("Invalid component count: must be 1, 2, 3, or 4. Got: ", std::to_string(components));
		return {};
	}

	switch (datatype)
	{
	case API::Core::BufferDataType::_FLOAT:
		format.InternalFormat = (components == 1) ? GL_R32F
		                      : (components == 2) ? GL_RG32F
		                      : (components == 3) ? GL_RGB32F
		                                          : GL_RGBA32F;
		format.Type = GL_FLOAT;
		break;

	case API::Core::BufferDataType::_FLOAT16:
		format.InternalFormat = (components == 1) ? GL_R16F
		                      : (components == 2) ? GL_RG16F
		                      : (components == 3) ? GL_RGB16F
		                                          : GL_RGBA16F;
		format.Type = GL_HALF_FLOAT;
		break;

	case API::Core::BufferDataType::_DOUBLE:
		// Note: OpenGL doesn't have native double-precision texture formats
		// Using 32-bit float as fallback
		format.InternalFormat = (components == 1) ? GL_R32F
		                      : (components == 2) ? GL_RG32F
		                      : (components == 3) ? GL_RGB32F
		                                          : GL_RGBA32F;
		format.Type = GL_FLOAT;
		break;

	case API::Core::BufferDataType::_BYTE_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R8
		                      : (components == 2) ? GL_RG8
		                      : (components == 3) ? GL_RGB8
		                                          : GL_RGBA8;
		format.Type = GL_UNSIGNED_BYTE;
		break;

	case API::Core::BufferDataType::_BYTE:
		format.InternalFormat = (components == 1) ? GL_R8_SNORM
		                      : (components == 2) ? GL_RG8_SNORM
		                      : (components == 3) ? GL_RGB8_SNORM
		                                          : GL_RGBA8_SNORM;
		format.Type = GL_BYTE;
		break;

	case API::Core::BufferDataType::_SHORT:
		format.InternalFormat = (components == 1) ? GL_R16_SNORM
		                      : (components == 2) ? GL_RG16_SNORM
		                      : (components == 3) ? GL_RGB16_SNORM
		                                          : GL_RGBA16_SNORM;
		format.Type = GL_SHORT;
		break;

	case API::Core::BufferDataType::_SHORT_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R16
		                      : (components == 2) ? GL_RG16
		                      : (components == 3) ? GL_RGB16
		                                          : GL_RGBA16;
		format.Type = GL_UNSIGNED_SHORT;
		break;

	case API::Core::BufferDataType::_INT:
		format.InternalFormat = (components == 1) ? GL_R32I
		                      : (components == 2) ? GL_RG32I
		                      : (components == 3) ? GL_RGB32I
		                                          : GL_RGBA32I;
		format.Type = GL_INT;
		break;

	case API::Core::BufferDataType::_INT_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R32UI
		                      : (components == 2) ? GL_RG32UI
		                      : (components == 3) ? GL_RGB32UI
		                                          : GL_RGBA32UI;
		format.Type = GL_UNSIGNED_INT;
		break;

	case API::Core::BufferDataType::_NONE:
	default:
		LOG_GL_ERROR("Invalid or unsupported BufferDataType");
		return {};
	}

	return format;
}

