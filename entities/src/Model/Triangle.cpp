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
	glm::vec3 centroid;
	centroid.x = (vert1.x + vert2.x + vert3.x) / 3.0f;
	centroid.y = (vert1.y + vert2.y + vert3.y) / 3.0f;
	centroid.z = (vert1.z + vert2.z + vert3.z) / 3.0f;
	return centroid;
}

glm::vec3 Triangle::getNormal()
{
	glm::vec3 AB = vert1 - vert2;
	glm::vec3 AC = vert1 - vert3;
	glm::vec3 normal = glm::cross(AB, AC);
	printf("%f, %f, %f normal original \n", normal.x, normal.y, normal.z);


	// can place in positive x,y direction fine. Z direction is inveresed.
	// % TODO found normal issue. Normal is always calculated to be the same direction. This is beacuse the triangles dont know what "normal is" (i.e) the are all in the same direction.

	// % Todo fix ray accuracy issues
	glm::vec3 tnormal(normal.x, normal.z, normal.y);
	printf("%f, %f, %f tranvserse \n", tnormal.x, tnormal.y, tnormal.z);
	return glm::normalize(tnormal);
}
