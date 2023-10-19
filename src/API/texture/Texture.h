#pragma once

#include "vendor/stb_image/stb_image.h"

namespace API::Texture {
	enum class TextureType { DIFFUSE, SPECULAR, SHINE, NORMAL, HEIGHT, DEFAULT };

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual int Bind(const unsigned int slot = 0) = 0;
		virtual void Unbind() = 0;

		inline const std::string& GetPath() const { return m_Filepath; };
		inline int GetWidth() const { return m_Width; };
		inline int GetHeight() const { return m_Height; };
		inline int GetRendererID() const { return m_RendererID; };
		inline int GetBoundPort() const { return m_BoundID; };

		void SetType(TextureType type) { m_Type = type; };
		inline TextureType GetType() { return m_Type; };

		static Texture* Create(const std::string& path, const bool flipUV = false);

	protected:
		int m_BoundID = -1;
		unsigned int m_RendererID = 0;
		std::string m_Filepath;
		unsigned char* m_LocalBuffer;
		int m_Width = 0, m_Height = 0, m_BPP = 0;

		TextureType m_Type;
	};
}
