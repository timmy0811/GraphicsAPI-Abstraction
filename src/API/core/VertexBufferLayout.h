#pragma once

#include "Debug/Debug.h"

#include <vector>

namespace API::Core {
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	struct VertexBufferElement {
		ShaderDataType type;
		unsigned int components;
		unsigned char normalized;
		size_t size;

		static int GetAPIDataType(ShaderDataType dataType);
	};

	class VertexBufferLayout
	{
	public:
		static uint32_t ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
			}

			API_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}

		static uint32_t GetComponentCount(ShaderDataType dataType)
		{
			switch (dataType)
			{
			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			API_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	public:
		VertexBufferLayout() = default;

		void Push(ShaderDataType dataType = ShaderDataType::Float, bool normalize = false) {
			API::Core::VertexBufferElement element{ dataType, GetComponentCount(dataType), normalize, ShaderDataTypeSize(dataType) };
			m_Elements.push_back(element);
			m_Stride += (unsigned int)element.size;
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

		static VertexBufferLayout* Create();

	protected:
		std::vector<VertexBufferElement> m_Elements;
		unsigned int m_Stride = 0;
	};
}