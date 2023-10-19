#pragma once

#include "vendor/glm/glm.hpp"
#include "Debug/Debug.h"

#include <vector>

#define MAX_BUF 8

namespace API::Core {
	class Framebuffer
	{
	public:
		enum class DepthBufferType { WRITE_ONLY, WRITE_READ };

		enum BufferDataType {
			_FLOAT = 0x1406,
			_FLOAT16 = 1,
			_DOUBLE = 0x140A,
			_BYTE_UNSIGNED = 0x1401,
			_BYTE = 0x1400,
			_SHORT = 0x1402,
			_SHORT_UNSIGNED = 0x1403,
			_INT_UNSIGNED = 0x1405,
			_INT = 0x1404
		};

		enum BufferFormat {
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

			RGBA = 0x1908,
			RGB = 0x1907,
			RG = 0x8227,
			R = 0x2002
		};

	public:
		virtual ~Framebuffer() = default;

		virtual void Bind(unsigned int Framebuffer) = 0;

		virtual void Bind() const = 0;
		virtual void BindAndClear() = 0;
		virtual void Unbind() = 0;

		virtual void BindTextures(const unsigned int startSlot = 0) = 0;
		virtual void BindTexture(int index, const unsigned int startSlot = 0) = 0;
		virtual unsigned int BindDepthTexture(const unsigned int slot) = 0;

		virtual bool PushColorAttribute(const char channel = 3, BufferDataType dataType = BufferDataType::_FLOAT, const void* data = nullptr) = 0;
		virtual bool PushColorAttribute(unsigned int internalFormat = 0x881A, unsigned int format = 0x1908, unsigned int dataType = 0x1406, const void* data = nullptr) = 0;

		virtual inline size_t AttachementCount() const = 0;
		virtual inline bool Validate() const = 0;
		virtual inline void Resize(const glm::ivec2& size) { m_Width = size.x; m_Height = size.y; }

		static Framebuffer* Create(const glm::ivec2& size, bool attachDepth = true, DepthBufferType depthType = DepthBufferType::WRITE_ONLY);

	protected:
		unsigned int m_Width, m_Height;
	};
}