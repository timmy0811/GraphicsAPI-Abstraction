#pragma once

namespace API::Core {
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual unsigned int GetCount() const { return m_Count; }

		static IndexBuffer* Create(const unsigned int* data, unsigned int count);

	protected:
		unsigned int m_Count;
	};
}