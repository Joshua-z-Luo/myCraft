#include "Ray.h"

Ray::Ray(const glm::vec3 origin, const glm::vec3 direction)
{
	this->origin = origin;
	this->direction = glm::normalize(direction);

}

/*
Checks if ray intersects block.
*/
bool Ray::rayIntersectsBlock(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t)
{
    const float EPSILON = 0.001f;

    glm::vec3 edge1, edge2, h, s, q;
    float a, f, u, v;

    edge1 = v1 - v0;
    edge2 = v2 - v0;
    h = glm::cross(direction, edge2);
    a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1.0f / a;
    s = origin - v0;
    u = f * glm::dot(s, h);

    if (u < 0.0f || u > 1.0f)
        return false;

    q = glm::cross(s, edge1);
    v = f * glm::dot(direction, q);

    if (v < 0.0f || u + v > 1.0f)
        return false;

    float r = f * glm::dot(edge2, q);

    return r > EPSILON;
}



