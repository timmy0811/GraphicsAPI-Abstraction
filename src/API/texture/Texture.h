#pragma once

#include <string>
#include <cstdint>

namespace API::Texture
{
	enum class TextureType { DIFFUSE, SPECULAR, SHINE, NORMAL, HEIGHT, DEFAULT };

	enum class TextureFilter
	{
		NEAREST, LINEAR, MIPMAP_NEAREST, MIPMAP_LINEAR, NEAREST_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST, LINEAR_MIPMAP_LINEAR
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint64_t MakeResident() = 0;
		virtual uint64_t GenerateHandle() = 0;

		virtual int Bind(unsigned int slot = 0) = 0;
		virtual void Unbind() = 0;

		[[nodiscard]] inline const std::string& GetPath() const { return m_Filepath; }
		[[nodiscard]] inline int GetWidth() const { return m_Width; }
		[[nodiscard]] inline int GetHeight() const { return m_Height; }
		[[nodiscard]] inline unsigned int GetRendererID() const { return m_RendererID; }
		[[nodiscard]] inline int GetBoundPort() const { return m_BoundID; }
		[[nodiscard]] inline uint64_t GetHandle() const { return Handle; }

		void SetType(const TextureType type) { m_Type = type; }
		[[nodiscard]] inline TextureType GetType() const { return m_Type; }
		[[nodiscard]] inline bool GetError() const { return Error; }

		static Texture* Create(const std::string& path, TextureFilter filter = TextureFilter::LINEAR,
		                       bool flipUV = false);

		static std::string TextureTypeToString(const TextureType type)
		{
			switch (type)
			{
			case TextureType::DIFFUSE: return "Diffuse";
			case TextureType::SPECULAR: return "Specular";
			case TextureType::SHINE: return "Shine";
			case TextureType::NORMAL: return "Normal";
			case TextureType::HEIGHT: return "Height";
			case TextureType::DEFAULT: return "Default";
			}
			return "Unknown";
		}

	protected:
		int m_BoundID = -1;
		unsigned int m_RendererID = 0;
		int m_Width = 0, m_Height = 0, m_BPP = 0;

		std::string m_Filepath;
		unsigned char* m_LocalBuffer = nullptr;

		bool isResident = false;
		uint64_t Handle = 0;
		bool Error = false;

		TextureType m_Type = {};
	};
}
