#pragma once

#include "vendor/glm/glm.hpp"
#include "API/core/Shader.h"

namespace OpenGL::Core
{
	class Shader_OpenGL final : public API::Core::Shader
	{
	public:
		Shader_OpenGL(const std::string& path_vert, const std::string& path_frag);
		~Shader_OpenGL() override;

		void Bind() const override;
		void Unbind() const override;

		// --- Uniforms ---
		void SetUniform1i(const std::string& name, int v0) override;
		void SetUniform2i(const std::string& name, int v0, int v1) override;
		void SetUniform3i(const std::string& name, int v0, int v1, int v2) override;
		void SetUniform4i(const std::string& name, int v0, int v1, int v2, int v3) override;

		void SetUniform1f(const std::string& name, float v0) override;
		void SetUniform2f(const std::string& name, float v0, float v1) override;
		void SetUniform3f(const std::string& name, float v0, float v1, float v2) override;
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;

		void SetUniform1iv(const std::string& name, unsigned int size, int* v) override;
		void SetUniform1fv(const std::string& name, unsigned int size, float* v) override;
		void SetUniform3fv(const std::string& name, unsigned int size, glm::vec3* v) override;

		// Custom Structures
		void SetUniformMaterial(const std::string& name, API::material::Material& m) override;

		void SetUniformConstantLight(const std::string& name, API::light::ConstantLight& m) override;
		void SetUniformSpotLight(const std::string& name, API::light::Spotlight& m) override;
		void SetUniformPointLight(const std::string& name, API::light::PointLight& m) override;
		void SetUniformDirectionalLight(const std::string& name, API::light::DirectionalLight& m) override;

		void SetUniformConstantLight(const std::string& name, API::light::ConstantLight& m, unsigned int index) override;
		void SetUniformSpotLight(const std::string& name, API::light::Spotlight& m, unsigned int index) override;
		void SetUniformPointLight(const std::string& name, API::light::PointLight& m, unsigned int index) override;
		void SetUniformDirectionalLight(const std::string& name, API::light::DirectionalLight& m, unsigned int index) override;

		void SetUniformMat4f(const std::string& name, const glm::mat4& mat) override;

	private:
		unsigned int m_RendererID;

		mutable std::unordered_map<std::string, int> m_UniformLacationCache{};

		int GetUniformLocation(const std::string& name) const;

		static std::string StringFromPath(const std::string& path);
		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		static unsigned int CompileShader(unsigned int type, const std::string& source);
		static ShaderProgramSource ParseShader(const std::string& path_vertex, const std::string& path_frag);
	};
}
