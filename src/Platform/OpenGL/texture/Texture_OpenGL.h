#pragma once

#include "API/texture/Texture.h"

namespace OpenGL::Texture
{
	class Texture_OpenGL final : public API::Texture::Texture
	{
	public:
		Texture_OpenGL(const std::string& path, API::Texture::TextureFilter filter, bool flipUV);
		~Texture_OpenGL() override;

		uint64_t MakeResident() override;
		uint64_t GenerateHandle() override;

		int Bind(unsigned int slot) override;
		void Unbind() override;

	private:
		static int MapGLFilter(API::Texture::TextureFilter filter);
	};
}
