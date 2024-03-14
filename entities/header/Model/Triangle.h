#pragma once

#include <glm/gtc/noise.hpp>

class Triangle
{
public:
	glm::vec3 origin;
	glm::vec3 vert1;
	glm::vec3 vert2;
	glm::vec3 vert3;
	int faceID;
	Triangle(glm::vec3 origin, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, int face);
	Triangle();
	glm::vec3 getTriangleCenter();
	glm::vec3 getNormal();


	// glm::vec3 checkIfBackFacep(glm::vec3, );

};

