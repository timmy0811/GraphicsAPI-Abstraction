#pragma once

#include "Misc/structs/Helper.hpp"
#include "Misc/structs/Primitive.hpp"

#include "API/core/VertexArray.h"
#include "API/core/IndexBuffer.h"
#include "API/core/Shader.h"
#include "API/texture/Texture.h"

#include <memory>
#include <map>
#include <string>

namespace API::Misc {
	struct Sprite {
		Sprite(const std::string& path, const glm::vec2& position, const glm::vec2& size, const bool flipUV = false) {
			this->Path = path;
			this->Position = position;
			this->Size = size;
			this->FlipUvs = flipUV;

			Uvs.u0 = { 0.f, 1.f };
			Uvs.u1 = { 1.f, 1.f };
			Uvs.u2 = { 1.f, 0.f };
			Uvs.u3 = { 0.f, 0.f };
		}

		Sprite(const std::string& path, const glm::vec2& position, const glm::vec2& size, Misc::Vec2_4 uvs, const bool flipUV = false) {
			this->Path = path;
			this->Position = position;
			this->Size = size;
			this->FlipUvs = flipUV;

			Uvs = uvs;
		}

		Sprite() = default;

		unsigned int Id;
		std::string Path;
		glm::vec2 Position;
		glm::vec2 Size;
		Misc::Vec2_4 Uvs;

		bool FlipUvs;
	};

	struct SpriteBlueprint : public Sprite {
		primitive::vertex::Sprite2DVertex vertices[4];

		SpriteBlueprint(const std::string& path, const glm::vec2& position, const glm::vec2& size, const bool flipUV = false) :Sprite(path, position, size, flipUV) {}
		SpriteBlueprint(const std::string& path, const glm::vec2& position, const glm::vec2& size, Misc::Vec2_4 uvs, const bool flipUV = false) :Sprite(path, position, size, uvs, flipUV) {}
	};

	class SpriteRenderer {
	public:
		SpriteRenderer(int maxSprites, glm::uvec2 samplerSlotRange, const int slotDefault, glm::vec2 winSize, const std::string& shaderVert, const std::string& shaderFrag);
		~SpriteRenderer();

		void Draw() const;

		void PushAll();
		void PopAll();
		void PopSprite(unsigned int id);

		int PushSprite(unsigned int id);
		unsigned int PushSprite(const Sprite& sprite);
		unsigned int PushSprite(const std::string& path, const glm::vec2& position, const glm::vec2& size, Misc::Vec2_4 uvs, const bool flipUV = false);
		unsigned int PushSprite(const std::string& path, const glm::vec2& position, const glm::vec2& size, const bool flipUV = false);

		void TransformSprite(const Misc::Vec2_4& uvs, unsigned int id);
		void TransformSprite(const glm::vec2& direction, unsigned int id);
		void SetSpritePosition(const glm::vec2& position, unsigned int id);

		void DeleteSprite(unsigned int id);
		void DeleteAll();

		void BindTextures();

	private:
		void RefreshVertBuffer();
		void UpdateSamplerArray();

	private:
		std::shared_ptr<API::Core::VertexBuffer> m_VB;
		std::shared_ptr<API::Core::IndexBuffer> m_IB;
		std::shared_ptr<API::Core::VertexBufferLayout> m_VBLayout;
		std::shared_ptr<API::Core::VertexArray> m_VA;

		glm::mat4 m_MatProjection;
		glm::mat4 m_MatView;
		glm::vec3 m_MatTranslation;

		unsigned int m_SamplerRangeLow;
		unsigned int m_SamplerRangeHigh;

		std::shared_ptr<Core::Shader> m_Shader;
		size_t m_Triangles = 0;
		int m_BindSlotStart = 0;

		std::vector<Texture::Texture*> m_Samplers;
		std::map<unsigned int, SpriteBlueprint*> m_Sprites;
		std::vector< SpriteBlueprint*> m_SpritesOnScreen;

		unsigned int n_IdPtr;
		size_t m_SamplerPtr;
	};
}
