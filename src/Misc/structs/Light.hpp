#pragma once

#include "vendor/glm/glm.hpp"

namespace API::light {
	struct ConstantLight {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct DirectionalLight {
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct Spotlight {
		glm::vec3 position;
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;
	};

	struct PointLight {
		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		float constant;
		float linear;
		float quadratic;
	};
}