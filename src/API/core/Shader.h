#pragma once

#include "vendor/glm/glm.hpp"
#include "Debug/Debug.h"

#include "Misc/structs/Material.hpp"
#include "Misc/structs/Light.hpp"

namespace API::Core {

	// Inherit this class to create own implementations for custom structures

	class Shader
	{
	public:
		struct ShaderProgramSource {
			std::string VertexSource;
			std::string FragmentSource;
		};

	public:
		Shader(const std::string& path_vert, const std::string& path_frag)
			:m_PathVert(path_vert), m_PathFrag(path_frag) {}

		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// --- Uniforms ---
		virtual void SetUniform1i(const std::string& name, int v0) = 0;
		virtual void SetUniform2i(const std::string& name, int v0, int v1) = 0;
		virtual void SetUniform3i(const std::string& name, int v0, int v1, int v2) = 0;
		virtual void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3) = 0;

		virtual void SetUniform1f(const std::string& name, float v0) = 0;
		virtual void SetUniform2f(const std::string& name, float v0, float v1) = 0;
		virtual void SetUniform3f(const std::string& name, float v0, float v1, float v2) = 0;
		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;

		virtual void SetUniform1iv(const std::string& name, unsigned int size, int* v) = 0;
		virtual void SetUniform1fv(const std::string& name, unsigned int size, float* v) = 0;
		virtual void SetUniform3fv(const std::string& name, unsigned int size, glm::vec3* v) = 0;

		// Custom Structures
		virtual void SetUniformMaterial(const std::string& name, material::Material& m) = 0;

		virtual void SetUniformConstantLight(const std::string& name, light::ConstantLight& m) = 0;
		virtual void SetUniformSpotLight(const std::string& name, light::Spotlight& m) = 0;
		virtual void SetUniformPointLight(const std::string& name, light::PointLight& m) = 0;
		virtual void SetUniformDirectionalLight(const std::string& name, light::DirectionalLight& m) = 0;

		virtual void SetUniformConstantLight(const std::string& name, light::ConstantLight& m, unsigned int index) = 0;
		virtual void SetUniformSpotLight(const std::string& name, light::Spotlight& m, unsigned int index) = 0;
		virtual void SetUniformPointLight(const std::string& name, light::PointLight& m, unsigned int index) = 0;
		virtual void SetUniformDirectionalLight(const std::string& name, light::DirectionalLight& m, unsigned int index) = 0;

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& mat) = 0;
		// ----------------

		static Shader* Create(const std::string& path_vert, const std::string& path_frag);

	protected:
		const std::string& m_PathVert;
		const std::string& m_PathFrag;
	};
}