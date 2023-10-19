#pragma once

#include "Debug/Debug.h"

#include "API/core/VertexBuffer.h"
#include "API/core/VertexArray.h"
#include "API/core/VertexBufferLayout.h"
#include "API/core/IndexBuffer.h"
#include "API/core/Shader.h"

#include "API/texture/Texture.h"
#include "Misc/structs/Primitive.hpp"

#include <vector>

namespace API::Model {
	class Mesh
	{
	public:
		Mesh(std::vector<API::primitive::vertex::VertexMesh> vertices, std::vector<unsigned int> indices, std::vector<API::Texture::Texture*> textures);

		void Draw(Core::Shader& shader);

	private:
		std::vector<primitive::vertex::VertexMesh> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Texture::Texture*> textures;

		std::unique_ptr<Core::VertexArray> m_VA;
		std::unique_ptr<Core::VertexBuffer> m_VB;
		std::unique_ptr<Core::VertexBufferLayout> m_VBLayout;
		std::unique_ptr<Core::IndexBuffer> m_IB;

		void LoadTextures(Core::Shader& shader);
	};
}
