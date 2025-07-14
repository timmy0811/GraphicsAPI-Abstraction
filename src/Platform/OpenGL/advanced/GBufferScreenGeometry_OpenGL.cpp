#include "glpch.h"
#include "GBufferScreenGeometry_OpenGL.h"

#include "vendor/glm/glm.hpp"
#include <vendor/glm/ext/matrix_clip_space.hpp>

#include "GL/glew.h"

OpenGL::Advanced::GBufferScreenGeometry_OpenGL::GBufferScreenGeometry_OpenGL(const unsigned int width, const unsigned int height)
	: Width(width), Height(height)
{
	ProjectionMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

	constexpr unsigned int index[] = {
		0, 1, 2, 2, 3, 0
	};

	IBO.reset(API::Core::IndexBuffer::Create(index, 6));
	VBO.reset(API::Core::VertexBuffer::Create(4, sizeof(float) * 5));

	constexpr float vert[] = {
		// Positions        // UVs
		-1.f, -1.f, 0.f, 0.f, 0.f, // Bottom-left
		1.f, -1.f, 0.f, 1.f, 0.f, // Bottom-right
		1.f, 1.f, 0.f, 1.f, 1.f, // Top-right
		-1.f, 1.f, 0.f, 0.f, 1.f // Top-left
	};

	VBO->Bind();
	VBO->AddVertexData(vert, sizeof(float) * 5 * 4);

	VBL.reset(API::Core::VertexBufferLayout::Create());
	VBL->Push(API::Core::ShaderDataType::Float3);
	VBL->Push(API::Core::ShaderDataType::Float2);

	VAO.reset(API::Core::VertexArray::Create());
	VAO->AddBuffer(*VBO, *VBL);
}

void OpenGL::Advanced::GBufferScreenGeometry_OpenGL::Draw(API::Core::Shader* shadingPassShader)
{
	VAO->Bind();
	IBO->Bind();
	shadingPassShader->Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::Advanced::GBufferScreenGeometry_OpenGL::Resize(const unsigned int width, const unsigned int height)
{
	Width = width;
	Height = height;

	ProjectionMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}
