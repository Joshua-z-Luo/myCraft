#include "../../header/Model/Triangle.h"

Triangle::Triangle(glm::vec3 origin, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3)
{
	this->origin = origin;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;
}

Triangle::Triangle()
{
}

glm::vec3 Triangle::getTriangleCenter()
{
	return glm::vec3();
}
