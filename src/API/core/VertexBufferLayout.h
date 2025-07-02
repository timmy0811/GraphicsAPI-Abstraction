#pragma once

#include "Debug/Debug.h"

#include <vector>

namespace API::Core
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	struct VertexBufferElement
	{
		ShaderDataType type;
		unsigned int components;
		unsigned char normalized;
		size_t size;

		static int GetAPIDataType(ShaderDataType dataType);
	};

	class VertexBufferLayout
	{
	public:
		static uint32_t ShaderDataTypeSize(const ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float: return sizeof(float);
			case ShaderDataType::Float2: return sizeof(float) * 2;
			case ShaderDataType::Float3: return sizeof(float) * 3;
			case ShaderDataType::Float4: return sizeof(float) * 4;
			case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
			case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;
			case ShaderDataType::Int: return sizeof(int);
			case ShaderDataType::Int2: return sizeof(int) * 2;
			case ShaderDataType::Int3: return sizeof(int) * 3;
			case ShaderDataType::Int4: return sizeof(int) * 4;
			case ShaderDataType::Bool: return sizeof(bool);
			default: break;
			}

			API_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

		static uint32_t GetComponentCount(const ShaderDataType dataType)
		{
			switch (dataType)
			{
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3: return 3 * 3;
			case ShaderDataType::Mat4: return 4 * 4;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 2;
			case ShaderDataType::Int3: return 3;
			case ShaderDataType::Int4: return 4;
			case ShaderDataType::Bool: return 1;
			default: break;
			}

			API_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

	public:
		VertexBufferLayout() = default;

		void Push(const ShaderDataType dataType = ShaderDataType::Float, const bool normalize = false)
		{
			const VertexBufferElement element{dataType, GetComponentCount(dataType), normalize, ShaderDataTypeSize(dataType)};
			m_Elements.push_back(element);
			m_Stride += (unsigned int)element.size;
		}

		[[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		[[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }

		static VertexBufferLayout* Create();

	protected:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};
}
