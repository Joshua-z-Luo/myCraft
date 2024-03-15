#include "../../header/Model/Triangle.h"

Triangle::Triangle(glm::vec3 origin, glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, int face)
{
	this->origin = origin;
	this->vert1 = vert1;
	this->vert2 = vert2;
	this->vert3 = vert3;
	this->faceID = face;
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
	//printf("%f, %f, %f normal original \n", normal.x, normal.y, normal.z);



	glm::vec3 tnormal(normal.x * -1, normal.z * -1, normal.y * -1);
	//printf("%f, %f, %f tranvserse \n", tnormal.x, tnormal.y, tnormal.z);
	return glm::normalize(tnormal);
}
