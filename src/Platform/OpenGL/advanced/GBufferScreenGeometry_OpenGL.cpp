#include "glpch.h"
#include "GBufferScreenGeometry_OpenGL.h"

#include "vendor/glm/glm.hpp"
#include <vendor/glm/ext/matrix_clip_space.hpp>

OpenGL::Advanced::GBufferScreenGeometry_OpenGL::GBufferScreenGeometry_OpenGL(unsigned int width, unsigned int height)
	:Width(width), Height(height)
{
	ProjectionMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

	unsigned int index[] = {
		0, 1, 2, 2, 3, 0
	};

	IBO.reset(API::Core::IndexBuffer::Create(index, 6));
	VBO.reset(API::Core::VertexBuffer::Create(4, sizeof(float) * 3));

	float vert[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		-1.f, 1.f, 0.f
	};

	VBO->Bind();
	VBO->AddVertexData(vert, sizeof(float) * 3 * 4);

	VBL.reset(API::Core::VertexBufferLayout::Create());
	VBL->Push(API::Core::ShaderDataType::Float3);

	VAO.reset(API::Core::VertexArray::Create());
	VAO->AddBuffer(*VBO, *VBL);
}

void OpenGL::Advanced::GBufferScreenGeometry_OpenGL::Draw(API::Core::Shader* shadingPassShader)
{
	VAO->Bind();
	IBO->Bind();

	shadingPassShader->Bind();
	shadingPassShader->SetUniformMat4f("u_Projection", ProjectionMat);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::Advanced::GBufferScreenGeometry_OpenGL::Resize(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;

	ProjectionMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}