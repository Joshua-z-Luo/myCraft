#pragma once
#include <glm/glm.hpp>
#include "../entities/header/Model/Triangle.h"

class Ray
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(const glm::vec3 origin, const glm::vec3 direction);
	bool rayIntersectsBlock(const Triangle& triangle, float& t);
	bool rayNormalCheck(Triangle triangle);
};

