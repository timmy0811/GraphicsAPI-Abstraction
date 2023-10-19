#pragma once

#define _AMD64_
#define NOMINMAX

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

// TODO: Use Factory Create for Core Features

namespace API::Model {
	class Model3D
	{
	public:
		Model3D(const char* path);
		~Model3D();

		void Draw(Core::Shader& shader);

	private:
		std::vector<Mesh> m_Meshes;
		std::string m_Directory;

		std::vector<Texture::Texture*> m_LoadedTextures;

		void Load(const std::string& path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture::Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type);
	};
}
