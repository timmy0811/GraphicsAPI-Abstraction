#include "glpch.h"
#include "Texture_OpenGL.h"

#include "Debug/Debug.h"

#include <GLEW/glew.h>

OpenGL::Texture::Texture_OpenGL::Texture_OpenGL(const std::string& path, const bool flipUV)
{
	m_Filepath = path;
	m_LocalBuffer = nullptr;
	GLCall(glActiveTexture(GL_TEXTURE0));

	if (flipUV) stbi_set_flip_vertically_on_load(1);
	else stbi_set_flip_vertically_on_load(0);

	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	if (!m_LocalBuffer) LOG_GL_ERROR("Could not load {}", path);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	{
		constexpr int filter = GL_NEAREST; // GL_LINEAR

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter));
	}

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}

OpenGL::Texture::Texture_OpenGL::~Texture_OpenGL()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

int OpenGL::Texture::Texture_OpenGL::Bind(const unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	m_BoundID = static_cast<int>(slot);
	return m_BoundID;
}

void OpenGL::Texture::Texture_OpenGL::Unbind()
{
	GLCall(glActiveTexture(m_BoundID));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	m_BoundID = -1;
}