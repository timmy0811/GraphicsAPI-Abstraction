#pragma once

#include "vendor/glm/glm.hpp"

namespace API::material {
	struct Material {
		int texture;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shine;
	};
}