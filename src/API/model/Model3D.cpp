#include "glpch.h"
#include "Model3D.h"

void API::Model::Model3D::Load(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // Some models work with flipped UVs

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		// import.GetErrorString()
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	m_Directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void API::Model::Model3D::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

API::Model::Mesh API::Model::Model3D::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<primitive::vertex::VertexMesh> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture::Texture*> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		primitive::vertex::VertexMesh v;

		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		v.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		v.Normal = vector;

		v.TexID = 0.f;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			v.TexCoords = vec;
		}
		else
			v.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture::Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture::Texture*> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture::Texture*> shineMaps = LoadMaterialTextures(material, aiTextureType_SHININESS);
		textures.insert(textures.end(), shineMaps.begin(), shineMaps.end());

		std::vector<Texture::Texture*> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture::Texture*> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<API::Texture::Texture*> API::Model::Model3D::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture::Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;

		std::string path = (m_Directory + '/' + str.C_Str());

		for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
		{
			if (std::strcmp(m_LoadedTextures[j]->GetPath().data(), path.c_str()) == 0) {
				textures.push_back(m_LoadedTextures[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			Texture::Texture* texture = Texture::Texture::Create(path, false); // m_Directory + str ???

			switch (type) {
			case aiTextureType_DIFFUSE: {
				texture->SetType(Texture::TextureType::DIFFUSE);
				break;
			}
			case aiTextureType_SPECULAR: {
				texture->SetType(Texture::TextureType::SPECULAR);
				break;
			}
			case aiTextureType_SHININESS: {
				texture->SetType(Texture::TextureType::SHINE);
				break;
			}
			case aiTextureType_HEIGHT: {
				texture->SetType(Texture::TextureType::HEIGHT);
				break;
			}
			case aiTextureType_NORMALS: {
				texture->SetType(Texture::TextureType::NORMAL);
				break;
			}
			default:
				texture->SetType(Texture::TextureType::DEFAULT);
			}

			textures.push_back(texture);
			m_LoadedTextures.push_back(texture);			// ????
		}
	}
	return textures;
}

API::Model::Model3D::Model3D(const char* path)
{
	Load(path);
}

API::Model::Model3D::~Model3D()
{
	for (Texture::Texture* tex : m_LoadedTextures) {
		delete tex;
	}
}

void API::Model::Model3D::Draw(API::Core::Shader& shader)
{
	for (Mesh& mesh : m_Meshes) {
		mesh.Draw(shader);
	}
}