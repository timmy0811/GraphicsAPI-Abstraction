#pragma once

#include "vendor/glm/glm.hpp"

#include <vector>

namespace API::Advanced {
	class SSAO
	{
	public:
		SSAO();

		void GenerateSampleKernel(int samples = 64);
		virtual void GenerateSSAONoiseMap() = 0;
		glm::vec3* getKernelAllocator() { return &(m_Kernel[0]); }
		virtual void BindNoiseTex(const unsigned int slot) = 0;

		static inline SSAO* Create();

	protected:
		std::vector<glm::vec3> m_Kernel;
		unsigned int m_IdNoise;
	};
}