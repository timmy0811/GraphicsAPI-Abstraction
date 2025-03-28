#pragma once

#include "vendor/stb_image/stb_image.h"
#include "API/texture/Texture.h"

namespace OpenGL::Texture {
	class Texture_OpenGL : public API::Texture::Texture
	{
	public:
		Texture_OpenGL(const std::string& path, API::Texture::TextureFilter filter, const bool flipUV);
		~Texture_OpenGL();

		uint64_t MakeResident() override;
		uint64_t GenerateHandle() override;

		int Bind(const unsigned int slot = 0) override;
		void Unbind() override;

	private:
		int MapGLFilter(API::Texture::TextureFilter filter);
	};
}
