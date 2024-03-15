#include "Ray.h"

Ray::Ray(const glm::vec3 origin, const glm::vec3 direction)
{
	this->origin = origin;
	this->direction = glm::normalize(direction) * 0.5f;

}

/*
Checks if ray intersects block.
*/


/*
CURRENT PROBLEMS:

New ray + normal check works really well in determining if triangle 

*/


bool Ray::rayIntersectsBlock(const Triangle& triangle, float& t)
{
    // SOMETHING IS WRONG WITH RAY
    // CAN BE SHOWN BY CLICKING ON EDGES OF BLOCKS, NOT DETECTING BLOCKS THAT ARE TOO CLOSE.
    const float EPSILON = 0.01f;

    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = triangle.vert2 - triangle.vert1;
    edge2 = triangle.vert3 - triangle.vert1;
    h = glm::cross(direction, edge2);
    a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1.0f / a;
    s = origin - triangle.vert1;
    u = f * glm::dot(s, h);

    if (u < 0.0f || u > 1.0f)
        return false;

    q = glm::cross(s, edge1);
    v = f * glm::dot(direction, q);

    if (v < 0.0f || u + v > 1.0f)
        return false;

    float r = f * glm::dot(edge2, q);
    glm::vec3 intersectionPoint = origin + direction * r;


    return r > EPSILON;
}

bool Ray::rayNormalCheck(Triangle triangle)
{
    glm::vec3 normal = triangle.getNormal();
    glm::vec3 normalRay = glm::normalize(direction);
    float dotProduct = glm::dot(normal, normalRay);
    return dotProduct < 0.0f;
}



