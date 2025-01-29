#include "glpch.h"
#include "GBuffer_OpenGL.h"

#include "Debug/Log.h"

OpenGL::Advanced::GBuffer_OpenGL::GBuffer_OpenGL(unsigned int width, unsigned int height)
	: Width(width), Height(height)
{
	glGenFramebuffers(1, &IdGBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, IdGBuffer);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		LOG_GL_ERROR("[OpenGL Error] (" + std::to_string(status) + ")");
	}

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OpenGL::Advanced::GBuffer_OpenGL::Bind() const
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, IdGBuffer));
	GLCall(glViewport(0, 0, Width, Height));
}

void OpenGL::Advanced::GBuffer_OpenGL::BindAndClear()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, IdGBuffer));
	GLCall(glViewport(0, 0, Width, Height));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void OpenGL::Advanced::GBuffer_OpenGL::Unbind()
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

void OpenGL::Advanced::GBuffer_OpenGL::BindDepthTexture(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, DepthTarget));
}

void OpenGL::Advanced::GBuffer_OpenGL::BindTexture(unsigned int slot, unsigned int index)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, Targets[index].second));
}

void OpenGL::Advanced::GBuffer_OpenGL::BindTexture(const std::string& identifier, unsigned int index)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + index));
	GLCall(glBindTexture(GL_TEXTURE_2D, GetTargetInternalId(identifier)));
}

void OpenGL::Advanced::GBuffer_OpenGL::BindTextures(unsigned int startSlot)
{
	for (GLuint i = 0; i < Targets.size(); i++) {
		GLCall(glActiveTexture(GL_TEXTURE0 + startSlot + i));
		GLCall(glBindTexture(GL_TEXTURE_2D, Targets[i].second));
	}
}

unsigned int OpenGL::Advanced::GBuffer_OpenGL::GetTargetInternalId(const std::string& identifier)
{
	for (const auto& target : Targets) {
		if (target.first == identifier) {
			return target.second;
		}
	}

	LOG_GL_WARN("Target not found: " + identifier + ". Returning 0");
	return 0;
}

const std::string OpenGL::Advanced::GBuffer_OpenGL::GetTargetIdentifier(unsigned int internalId)
{
	for (const auto& target : Targets) {
		if (target.second == internalId) {
			return target.first;
		}
	}

	LOG_GL_WARN("Target not found: " + std::to_string(internalId) + ". Returning empty Identifier.");
	return "";
}

unsigned int OpenGL::Advanced::GBuffer_OpenGL::AddRenderTarget(const std::string& identifier, unsigned int width, unsigned int height, unsigned int components, API::Core::BufferDataType datatype, API::Core::WrapMethod wrap, void* data)
{
	Targets.push_back({ identifier, 0 });

	GLCall(glGenTextures(1, &Targets.back().second));
	GLCall(glBindTexture(GL_TEXTURE_2D, Targets.back().second));

	TextureFormat format = GetTextureFormat(components, datatype);
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format.InternalFormat, width, height, 0, format.Format, format.Type, data));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap));

	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<unsigned int>(Targets.size() - 1), GL_TEXTURE_2D, Targets.back().second, 0));

	return Targets.back().second;
}

unsigned int OpenGL::Advanced::GBuffer_OpenGL::AddRenderTarget(const std::string& identifier, unsigned int components, API::Core::BufferDataType datatype, API::Core::WrapMethod wrap, void* data)
{
	return AddRenderTarget(identifier, Width, Height, components, datatype, wrap, data);
}

unsigned int OpenGL::Advanced::GBuffer_OpenGL::AddDepthTarget(unsigned int width, unsigned int height, API::Core::DepthBufferType type)
{
	switch (type)
	{
	case API::Core::DepthBufferType::WRITE_ONLY:
		glGenRenderbuffers(1, &DepthTarget);
		glBindRenderbuffer(GL_RENDERBUFFER, DepthTarget);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DepthTarget);

		break;
	case API::Core::DepthBufferType::WRITE_READ:
		GLCall(glGenTextures(1, &DepthTarget));
		GLCall(glBindTexture(GL_TEXTURE_2D, DepthTarget));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, IdGBuffer));
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTarget, 0));

		GLCall(glDrawBuffer(GL_NONE));
		GLCall(glReadBuffer(GL_NONE));

		break;
	default:
		LOG_GL_WARN("DepthBufferType not supported!");
	}

	return DepthTarget;
}

unsigned int OpenGL::Advanced::GBuffer_OpenGL::AddDepthTarget(API::Core::DepthBufferType type)
{
	return AddDepthTarget(Width, Height, type);
}

bool OpenGL::Advanced::GBuffer_OpenGL::Validate()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, IdGBuffer));
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "[OpenGL Error] (" << std::to_string(status) << ")" << std::endl;
		return false;
	}

	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	return true;
}

OpenGL::Advanced::GBuffer_OpenGL::TextureFormat OpenGL::Advanced::GBuffer_OpenGL::GetTextureFormat(unsigned int components, API::Core::BufferDataType datatype)
{
	TextureFormat format;

	switch (components) {
	case 1: format.Format = GL_RED; break;
	case 2: format.Format = GL_RG; break;
	case 3: format.Format = GL_RGB; break;
	case 4: format.Format = GL_RGBA; break;
	default:
		LOG_GL_ERROR("Invalid component count: must be 1, 2, 3, or 4.");
		return {};
	}

	switch (datatype) {
	case API::Core::BufferDataType::_FLOAT:
		format.InternalFormat = (components == 1) ? GL_R32F :
			(components == 2) ? GL_RG32F :
			(components == 3) ? GL_RGB32F :
			GL_RGBA32F;
		format.Type = GL_FLOAT;
		break;

	case API::Core::BufferDataType::_FLOAT16:
		format.InternalFormat = (components == 1) ? GL_R16F :
			(components == 2) ? GL_RG16F :
			(components == 3) ? GL_RGB16F :
			GL_RGBA16F;
		format.Type = GL_HALF_FLOAT;
		break;

	case API::Core::BufferDataType::_DOUBLE:
		format.InternalFormat = (components == 1) ? GL_R32F :
			(components == 2) ? GL_RG32F :
			(components == 3) ? GL_RGB32F :
			GL_RGBA32F;
		format.Type = GL_DOUBLE;
		break;

	case API::Core::BufferDataType::_BYTE_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R8 :
			(components == 2) ? GL_RG8 :
			(components == 3) ? GL_RGB8 :
			GL_RGBA8;
		format.Type = GL_UNSIGNED_BYTE;
		break;

	case API::Core::BufferDataType::_BYTE:
		format.InternalFormat = (components == 1) ? GL_R8_SNORM :
			(components == 2) ? GL_RG8_SNORM :
			(components == 3) ? GL_RGB8_SNORM :
			GL_RGBA8_SNORM;
		format.Type = GL_BYTE;
		break;

	case API::Core::BufferDataType::_SHORT:
		format.InternalFormat = (components == 1) ? GL_R16_SNORM :
			(components == 2) ? GL_RG16_SNORM :
			(components == 3) ? GL_RGB16_SNORM :
			GL_RGBA16_SNORM;
		format.Type = GL_SHORT;
		break;

	case API::Core::BufferDataType::_SHORT_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R16 :
			(components == 2) ? GL_RG16 :
			(components == 3) ? GL_RGB16 :
			GL_RGBA16;
		format.Type = GL_UNSIGNED_SHORT;
		break;

	case API::Core::BufferDataType::_INT:
		format.InternalFormat = (components == 1) ? GL_R32I :
			(components == 2) ? GL_RG32I :
			(components == 3) ? GL_RGB32I :
			GL_RGBA32I;
		format.Type = GL_INT;
		break;

	case API::Core::BufferDataType::_INT_UNSIGNED:
		format.InternalFormat = (components == 1) ? GL_R32UI :
			(components == 2) ? GL_RG32UI :
			(components == 3) ? GL_RGB32UI :
			GL_RGBA32UI;
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