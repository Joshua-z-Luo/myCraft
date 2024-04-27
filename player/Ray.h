#pragma once
#include <glm/glm.hpp>

class Ray
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(const glm::vec3 origin, const glm::vec3 direction);
	bool rayIntersectsBlock(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t);
};

