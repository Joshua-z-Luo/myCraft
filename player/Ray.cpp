#include "Ray.h"

Ray::Ray(const glm::vec3 origin, const glm::vec3 direction)
{
	this->origin = origin;
	this->direction = glm::normalize(direction);

}

/*
Checks if ray intersects block.
*/


/*
CURRENT PROBLEMS:

SOLVED:
    - Fixed ray selecting wrong triangles during block placement by adding a function that checks if triangle normal is facing same direction as ray.
    - Fxied all directions except negative y direction. Solved bad normal calculations by making sure to convert from opengl cordinates to block cordinates when creating position of new block,
        however using opengl coordinates when checking if normal and ray form angle less then 90 degrees.

PERSISTANT ISSUES:
    - Ray has accuracy/detection issues, passing through parts of blocks on click. not triggering any sort of reaction. THIS ONLY OCCURS IN THE NEGATIVE Y DIRECTION (FRONT FACE OF BLOCKS)
    - Issue is not with sorting. When to close to block, and aiming at certain parts of a face, ray will hit missing triangle and pass throguh to other blocks.
    - Hitbox of front face is only very top of block. (negative y)

*/


bool Ray::rayIntersectsBlock(const Triangle& triangle, float& t)
{
    // SOMETHING IS WRONG WITH RAY
    // CAN BE SHOWN BY CLICKING ON EDGES OF BLOCKS, NOT DETECTING BLOCKS THAT ARE TOO CLOSE.
    const float EPSILON = 0.1f;

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

// 
bool Ray::rayNormalCheck(Triangle triangle)
{
    glm::vec3 normal = glm::normalize(triangle.getNormal());
    glm::vec3 normalRay = glm::normalize(direction);
    float dotProduct = glm::dot(normal, normalRay);
    printf(" direction face %d %f, %f, %f \n", triangle.faceID, normalRay.x, normalRay.y, normalRay.z);
    printf(" calc face %d %f, %f, %f, %f \n", triangle.faceID, normal.x, normal.y, normal.z, dotProduct);
    return dotProduct > 0.0f;
}


