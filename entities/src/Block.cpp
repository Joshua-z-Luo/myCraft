#include "header/Block.h"
#include "../../shaders/EBO.h"
#include "../../shaders/VBO.h"
#include "../../shaders/VAO.h"


Block::Block(GLfloat x, GLfloat y, GLfloat z)
{
    z = round(z);

    // Front face
    vertices[0] = { glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[1] = { glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[2] = { glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[3] = { glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Back face
    vertices[4] = { glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[5] = { glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[6] = { glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[7] = { glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.92f, 0.86f, 0.76f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Right face
    vertices[8] = { glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[9] = { glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[10] = { glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[11] = { glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Left face
    vertices[12] = { glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[13] = { glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[14] = { glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[15] = { glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.76f, 0.45f, 0.12f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Top face
    vertices[16] = { glm::vec3(x - 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.67f, 0.87f, 0.50f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[17] = { glm::vec3(x + 0.5f, y + 0.5f, z + 0.5f), glm::vec3(0.67f, 0.87f, 0.50f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[18] = { glm::vec3(x + 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.67f, 0.87f, 0.50f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[19] = { glm::vec3(x - 0.5f, y + 0.5f, z - 0.5f), glm::vec3(0.67f, 0.87f, 0.50f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Bottom face
    vertices[20] = { glm::vec3(x - 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.98f, 0.76f, 0.45f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
    vertices[21] = { glm::vec3(x + 0.5f, y - 0.5f, z + 0.5f), glm::vec3(0.98f, 0.76f, 0.45f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) };
    vertices[22] = { glm::vec3(x + 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.98f, 0.76f, 0.45f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) };
    vertices[23] = { glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f), glm::vec3(0.98f, 0.76f, 0.45f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) };

    // Indices for vertices order
    // Top face
    indices[0] = 16;
    indices[1] = 17;
    indices[2] = 18;
    indices[3] = 18;
    indices[4] = 19;
    indices[5] = 16;

    // Front face
    indices[6] = 0;
    indices[7] = 1;
    indices[8] = 2;
    indices[9] = 2;
    indices[10] = 3;
    indices[11] = 0;

    // Left face
    indices[12] = 12;
    indices[13] = 13;
    indices[14] = 14;
    indices[15] = 14;
    indices[16] = 15;
    indices[17] = 12;

    // Back face
    indices[18] = 4;
    indices[19] = 5;
    indices[20] = 6;
    indices[21] = 6;
    indices[22] = 7;
    indices[23] = 4;

    // Right face
    indices[24] = 8;
    indices[25] = 9;
    indices[26] = 10;
    indices[27] = 10;
    indices[28] = 11;
    indices[29] = 8;

    // Bottom face
    indices[30] = 20;
    indices[31] = 21;
    indices[32] = 22;
    indices[33] = 22;
    indices[34] = 23;
    indices[35] = 20;
}


GLfloat* Block::getVert()
{
	return vertices;
}

GLuint* Block::getInd()
{
	return indices;
}

glm::vec3* Block::getTriangles()
{
	glm::vec3 * result = new glm::vec3[36];
	for (int i = 0; i < 12; i++) {
		for (int x = i * 3; x < (i * 3) + 3; x++) {
			glm::vec3 temp(vertices[(indices[x] * 8)], vertices[(indices[x] * 8) + 1], vertices[(indices[x] * 8) + 2]);
			result[x] = temp;
		}
	}
	return result;
}
