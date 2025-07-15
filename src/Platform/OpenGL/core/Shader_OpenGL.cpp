#include "glpch.h"
#include "Shader_OpenGL.h"

#include <GL/glew.h>

OpenGL::Core::Shader_OpenGL::Shader_OpenGL(const std::string& path_vert, const std::string& path_frag)
	: Shader(path_vert, path_frag), m_RendererID(0)
{
	LOG_GL_TRACE("Compiling Shader: {}", path_vert.substr(0, path_vert.length() - 5));
	auto [VertexSource, FragmentSource] = ParseShader(path_vert, path_frag);
	m_RendererID = CreateShader(VertexSource, FragmentSource);
}

int OpenGL::Core::Shader_OpenGL::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLacationCache.find(name) != m_UniformLacationCache.end())
		return m_UniformLacationCache[name];

	GLCall(const int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		LOG_GL_WARN("Warning: uniform: {} cannot be found.", name);

	m_UniformLacationCache[name] = location;

	return location;
}

OpenGL::Core::Shader_OpenGL::~Shader_OpenGL()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void OpenGL::Core::Shader_OpenGL::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void OpenGL::Core::Shader_OpenGL::Unbind() const
{
	GLCall(glUseProgram(0));
}

void OpenGL::Core::Shader_OpenGL::SetUniform4f(const std::string& name, const float v0, const float v1, const float v2,
                                               const float v3)
{
	const int pos = GetUniformLocation(name);
	GLCall(glUniform4f(pos, v0, v1, v2, v3));
}

void OpenGL::Core::Shader_OpenGL::SetUniform1f(const std::string& name, const float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void OpenGL::Core::Shader_OpenGL::SetUniform1i(const std::string& name, const int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void OpenGL::Core::Shader_OpenGL::SetUniform2i(const std::string& name, const int v0, const int v1)
{
	GLCall(glUniform2i(GetUniformLocation(name), v0, v1));
}

void OpenGL::Core::Shader_OpenGL::SetUniform3i(const std::string& name, const int v0, const int v1, const int v2)
{
	GLCall(glUniform3i(GetUniformLocation(name), v0, v1, v2));
}

void OpenGL::Core::Shader_OpenGL::SetUniform4i(const std::string& name, const int v0, const int v1, const int v2,
                                               const int v3)
{
	GLCall(glUniform4i(GetUniformLocation(name), v0, v1, v2, v3));
}

void OpenGL::Core::Shader_OpenGL::SetUniform2f(const std::string& name, const float v0, const float v1)
{
	GLCall(glUniform2f(GetUniformLocation(name), v0, v1));
}

void OpenGL::Core::Shader_OpenGL::SetUniform1iv(const std::string& name, const unsigned int size, int* v)
{
	GLCall(glUniform1iv(GetUniformLocation(name), size, v));
}

void OpenGL::Core::Shader_OpenGL::SetUniform1fv(const std::string& name, const unsigned int size, float* v)
{
	GLCall(glUniform1fv(GetUniformLocation(name), size, v));
}

void OpenGL::Core::Shader_OpenGL::SetUniform3fv(const std::string& name, const unsigned int size, glm::vec3* v)
{
	GLCall(glUniform3fv(GetUniformLocation(name), size, &v->x));
}

void OpenGL::Core::Shader_OpenGL::SetUniform3f(const std::string& name, const float v0, const float v1, const float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void OpenGL::Core::Shader_OpenGL::SetUniformMaterial(const std::string& name, API::material::Material& m)
{
	GLCall(glUniform3f(GetUniformLocation(name + ".ambient"), m.ambient.r, m.ambient.g, m.ambient.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".diffuse"), m.diffuse.r, m.diffuse.g, m.diffuse.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".specular"), m.specular.r, m.specular.g, m.specular.b));
	GLCall(glUniform1f(GetUniformLocation(name + ".shine"), m.shine));
}

void OpenGL::Core::Shader_OpenGL::SetUniformConstantLight(const std::string& name, API::light::ConstantLight& m)
{
	GLCall(glUniform3f(GetUniformLocation(name + ".position"), m.position.r, m.position.g, m.position.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".ambient"), m.ambient.r, m.ambient.g, m.ambient.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".diffuse"), m.diffuse.r, m.diffuse.g, m.diffuse.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".specular"), m.specular.r, m.specular.g, m.specular.b));
}

void OpenGL::Core::Shader_OpenGL::SetUniformSpotLight(const std::string& name, API::light::Spotlight& m)
{
	GLCall(glUniform3f(GetUniformLocation(name + ".position"), m.position.r, m.position.g, m.position.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".direction"), m.direction.r, m.direction.g, m.direction.b));
	GLCall(glUniform1f(GetUniformLocation(name + ".cutOff"), m.cutOff));
	GLCall(glUniform1f(GetUniformLocation(name + ".outerCutOff"), m.outerCutOff));

	GLCall(glUniform3f(GetUniformLocation(name + ".ambient"), m.ambient.r, m.ambient.g, m.ambient.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".diffuse"), m.diffuse.r, m.diffuse.g, m.diffuse.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".specular"), m.specular.r, m.specular.g, m.specular.b));

	GLCall(glUniform1f(GetUniformLocation(name + ".constant"), m.constant));
	GLCall(glUniform1f(GetUniformLocation(name + ".linear"), m.linear));
	GLCall(glUniform1f(GetUniformLocation(name + ".quadratic"), m.quadratic));
}

void OpenGL::Core::Shader_OpenGL::SetUniformPointLight(const std::string& name, API::light::PointLight& m)
{
	GLCall(glUniform3f(GetUniformLocation(name + ".position"), m.position.r, m.position.g, m.position.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".ambient"), m.ambient.r, m.ambient.g, m.ambient.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".diffuse"), m.diffuse.r, m.diffuse.g, m.diffuse.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".specular"), m.specular.r, m.specular.g, m.specular.b));

	GLCall(glUniform1f(GetUniformLocation(name + ".constant"), m.constant));
	GLCall(glUniform1f(GetUniformLocation(name + ".linear"), m.linear));
	GLCall(glUniform1f(GetUniformLocation(name + ".quadratic"), m.quadratic));
}

void OpenGL::Core::Shader_OpenGL::SetUniformDirectionalLight(const std::string& name, API::light::DirectionalLight& m)
{
	GLCall(glUniform3f(GetUniformLocation(name + ".direction"), m.direction.r, m.direction.g, m.direction.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".ambient"), m.ambient.r, m.ambient.g, m.ambient.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".diffuse"), m.diffuse.r, m.diffuse.g, m.diffuse.b));
	GLCall(glUniform3f(GetUniformLocation(name + ".specular"), m.specular.r, m.specular.g, m.specular.b));
}

void OpenGL::Core::Shader_OpenGL::SetUniformConstantLight(const std::string& name, API::light::ConstantLight& m,
                                                          const unsigned int index)
{
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".position"), m.position.r, m.position
			.g, m.position.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".ambient"), m.ambient.r, m.ambient.g,
			m.ambient.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".diffuse"), m.diffuse.r, m.diffuse.g,
			m.diffuse.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".specular"), m.specular.r, m.specular
			.g, m.specular.b));
}

void OpenGL::Core::Shader_OpenGL::SetUniformSpotLight(const std::string& name, API::light::Spotlight& m,
                                                      const unsigned int index)
{
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".position"), m.position.r, m.position
			.g, m.position.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".direction"), m.direction.r, m.
			direction.g, m.direction.b));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".cutOff"), m.cutOff));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".outerCutOff"), m.outerCutOff));

	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".ambient"), m.ambient.r, m.ambient.g,
			m.ambient.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".diffuse"), m.diffuse.r, m.diffuse.g,
			m.diffuse.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".specular"), m.specular.r, m.specular
			.g, m.specular.b));

	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".constant"), m.constant));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".linear"), m.linear));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".quadratic"), m.quadratic));
}

void OpenGL::Core::Shader_OpenGL::SetUniformPointLight(const std::string& name, API::light::PointLight& m,
                                                       const unsigned int index)
{
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".position"), m.position.r, m.position
			.g, m.position.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".ambient"), m.ambient.r, m.ambient.g,
			m.ambient.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".diffuse"), m.diffuse.r, m.diffuse.g,
			m.diffuse.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".specular"), m.specular.r, m.specular
			.g, m.specular.b));

	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".constant"), m.constant));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".linear"), m.linear));
	GLCall(glUniform1f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".quadratic"), m.quadratic));
}

void OpenGL::Core::Shader_OpenGL::SetUniformDirectionalLight(const std::string& name, API::light::DirectionalLight& m,
                                                             const unsigned int index)
{
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".direction"), m.direction.r, m.
			direction.g, m.direction.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".ambient"), m.ambient.r, m.ambient.g,
			m.ambient.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".diffuse"), m.diffuse.r, m.diffuse.g,
			m.diffuse.b));
	GLCall(
		glUniform3f(GetUniformLocation(name + "[" + std::to_string(index) + "]" + ".specular"), m.specular.r, m.specular
			.g, m.specular.b));
}

void OpenGL::Core::Shader_OpenGL::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
	const int idex = GetUniformLocation(name);
	GLCall(glUniformMatrix4fv(idex, 1, GL_FALSE, &mat[0][0]));
}

API::Core::Shader::ShaderProgramSource OpenGL::Core::Shader_OpenGL::ParseShader(
	const std::string& path_vertex, const std::string& path_frag)
{
	const std::string& A = StringFromPath(path_vertex);
	const std::string& B = StringFromPath(path_frag);
	return {A, B};
}

unsigned int OpenGL::Core::Shader_OpenGL::CompileShader(const unsigned int type, const std::string& source)
{
	GLCall(const unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		auto message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::string msg = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
		LOG_GL_ERROR("Failed to compile {} shader!", msg);
		LOG_GL_ERROR("{}", message);
		GLCall(glDeleteShader(id));
	}

	return id;
}

std::string OpenGL::Core::Shader_OpenGL::StringFromPath(const std::string& path)
{
	std::ifstream stream(path);
	if (!stream.is_open())
	{
		throw std::runtime_error("Failed to open shader file: " + path);
	}

	std::string line;
	std::stringstream ss;
	bool isValid = false;

	std::string basePath = path.substr(0, path.find_last_of("/\\"));

	while (getline(stream, line))
	{
		if (line.find("//shader") != std::string::npos)
		{
			isValid = true;
		}
		else if (isValid)
		{
			if (line.find("#include") != std::string::npos)
			{
				size_t start = line.find_first_of("\"<") + 1;
				size_t end = line.find_last_of("\">");
				std::string includeFile = line.substr(start, end - start);

				std::string fullPath = basePath + "/" + includeFile;

				std::ifstream includeStream(fullPath);
				if (!includeStream.is_open())
				{
					throw std::runtime_error("Failed to open included file: " + fullPath);
				}

				std::stringstream includeContent;
				includeContent << includeStream.rdbuf();

				ss << includeContent.str() << "\n";
			}
			else
				ss << line << "\n";
		}
	}

	if (!isValid)
	{
		LOG_GL_ERROR("Shader file " + path + " does not contain a valid shader definition. Please ensure it starts with '//shader'.");
		throw std::runtime_error("Failed compile shader: " + path);
	}

	return ss.str();
}

unsigned int OpenGL::Core::Shader_OpenGL::CreateShader(const std::string& vertexShader,
                                                       const std::string& fragmentShader)
{
	GLCall(const unsigned int program = glCreateProgram());
	GLCall(const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	GLCall(const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}
