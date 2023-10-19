#include "glpch.h"
#include "SSAO.h"

#include "API/core/Renderer.h"
#include "Platform/OpenGL/advanced/SSAO_OpenGL.h"

#include <random>

API::Advanced::SSAO::SSAO()
{
	m_Kernel.reserve(64);
}

void API::Advanced::SSAO::GenerateSampleKernel(int samples)
{
	std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
	std::default_random_engine generator;
	for (unsigned int i = 0; i < 64; ++i)
	{
		glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);
		float scale = float(i) / 64.0f;

		scale = 0.1f + scale * scale * 0.9f;
		sample *= scale;
		m_Kernel.push_back(sample);
	}
}

inline API::Advanced::SSAO* API::Advanced::SSAO::Create()
{
	switch (API::Core::RendererContext::GetAPI())
	{
	case API::Core::RendererAPI::API_ENUM::None:    API_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case API::Core::RendererAPI::API_ENUM::OpenGL:  return new OpenGL::Advanced::SSAO_OpenGL();
	}

	API_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}