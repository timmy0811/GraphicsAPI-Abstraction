#pragma once

#include "vendor/glm/glm.hpp"

#include <GL/glew.h>

#define MAX_BUF 8

namespace API::Core
{
	enum BufferDataType
	{
		_FLOAT = 0x1406,
		_FLOAT16 = 1,
		_DOUBLE = 0x140A,
		_BYTE_UNSIGNED = 0x1401,
		_BYTE = 0x1400,
		_SHORT = 0x1402,
		_SHORT_UNSIGNED = 0x1403,
		_INT_UNSIGNED = 0x1405,
		_INT = 0x1404,
		_NONE = 0
	};

	enum WrapMethod
	{
		NEAREST = 0x2600,
		LINEAR = 0x2601,
		CLAMP_TO_EDGE = 0x812F,
		MIRRORED_REPEAT = 0x8370,
		REPEAT = 0x2901,
		CLAMP_TO_BORDER = 0x812D,
		MIRROR_CLAMP_TO_EDGE = 0x8743,

		NEAREST_MIPMAP_NEAREST = 0x2700,
		LINEAR_MIPMAP_NEAREST = 0x2701,
		NEAREST_MIPMAP_LINEAR = 0x2702,
		LINEAR_MIPMAP_LINEAR = 0x2703
	};

	enum class DepthBufferType { WRITE_ONLY, WRITE_READ };

	class Framebuffer
	{
	public:
		enum BufferFormat
		{
			RGBA32F = 0x8814,
			RGB32F = 0x8815,
			RG32F = 0x8230,
			R32F = 0x822E,

			RGBA16F = 0x881A,
			RGB16F = 0x881B,
			RG16F = 0x822F,
			R16F = 0x822D,

			RGBA32UI = 0x8D70,
			RGB32UI = 0x8D71,
			RG32UI = 0x823C,
			R32UI = 0x8236,

			RGBA16UI = 0x8D76,
			RGB16UI = 0x8D77,
			RG16UI = 0x823A,
			R16UI = 0x8234,

			RGBA8UI = 0x8D7C,
			RGB8UI = 0x8D7D,
			RG8UI = 0x8238,
			R8UI = 0x8232,

			RGBA32I = 0x8D82,
			RGB32I = 0x8D83,
			RG32I = 0x823B,
			R32I = 0x8235,

			RGBA16I = 0x8D88,
			RGB16I = 0x8D89,
			RG16I = 0x8239,
			R16I = 0x8233,

			RGBA8I = 0x8D8E,
			RGB8I = 0x8D8F,
			RG8I = 0x8237,
			R8I = 0x8231,

			RGBA8 = 0x8058,
			RGB8 = 0x8051,
			RG8 = 0x822B,
			R8 = 0x8229,

			RGBA = 0x1908,
			RGB = 0x1907,
			RG = 0x8227,
			R = 0x2002
		};

	public:
		virtual ~Framebuffer() = default;

		virtual void Bind(unsigned int framebufferId) = 0;

		[[nodiscard]] virtual int GetInternalId() const = 0;

		virtual void Bind() const = 0;
		virtual void BindAndClear() = 0;
		virtual void Unbind() = 0;

		virtual void BindTextures(unsigned int startSlot = 0) = 0;
		virtual void BindTexture(int index, unsigned int startSlot = 0) = 0;
		virtual unsigned int BindDepthTexture(unsigned int slot) = 0;

		virtual bool PushColorAttribute(char channel = 3, BufferDataType dataType = _FLOAT, const void* data = nullptr) = 0;
		virtual bool PushColorAttribute(unsigned int internalFormat = 0x881A, unsigned int format = 0x1908, unsigned int dataType = 0x1406, const void* data = nullptr) = 0;

		virtual unsigned int GetColorAttachmentTextureID(unsigned int index) = 0;

		virtual void SetColorAttachmentFilter(unsigned int index, unsigned int filter) = 0;

		[[nodiscard]] virtual size_t AttachmentCount() const = 0;
		virtual bool Validate() const = 0;

		virtual void Resize(const glm::ivec2& size)
		{
			m_Width = size.x;
			m_Height = size.y;
		}

		static Framebuffer* Create(const glm::ivec2& size, bool attachDepth, DepthBufferType depthType = DepthBufferType::WRITE_ONLY);
		static Framebuffer* Create(const glm::ivec2& size);

	protected:
		unsigned int m_Width{}, m_Height{};
	};
}
