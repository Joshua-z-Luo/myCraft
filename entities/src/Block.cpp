#include "header/Block.h"
#include "../../shaders/EBO.h"
#include "../../shaders/VBO.h"
#include "../../shaders/VAO.h"


Block::Block(GLfloat x, GLfloat y, GLfloat z)
{
	z = round(z);
	// Vertices coordinates
	/*
	vertices[0] = x + -0.25f; 
	vertices[1] = z + 0.0f;
	vertices[2] = y + 0.25f;
	vertices[3] = 0.83f;
	vertices[4] = 0.70f;
	vertices[5] = 0.44f;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;

	vertices[8] = x + -0.25f;
	vertices[9] = z + 0.0f;
	vertices[10] = y + -0.25f;
	vertices[11] = 0.83f;
	vertices[12] = 0.70f;
	vertices[13] = 0.44f;
	vertices[14] = 5.0f;
	vertices[15] = 0.0f;

	vertices[16] = x + 0.25f;
	vertices[17] = z + 0.0f;
	vertices[18] = y + -0.25f;
	vertices[19] = 0.83f;
	vertices[20] = 0.70f;
	vertices[21] = 0.44f;
	vertices[22] = 5.0f;
	vertices[23] = 5.0f;

	vertices[24] = x + 0.25f;
	vertices[25] = z + 0.0f;
	vertices[26] = y + 0.25f;
	vertices[27] = 0.83f;
	vertices[28] = 0.70f;
	vertices[29] = 0.44f;
	vertices[30] = 0.0f;
	vertices[31] = 5.0f;

	vertices[32] = x + -0.25f;
	vertices[33] = z + 0.5f;
	vertices[34] = y + 0.25f;
	vertices[35] = 0.83f;
	vertices[36] = 0.70f;
	vertices[37] = 0.44f;
	vertices[38] = 0.0f;
	vertices[39] = 0.0f;

	vertices[40] = x + -0.25f;
	vertices[41] = z + 0.5f;
	vertices[42] = y + -0.25f;
	vertices[43] = 0.83f;
	vertices[44] = 0.70f;
	vertices[45] = 0.44f;
	vertices[46] = 5.0f;
	vertices[47] = 0.0f;

	vertices[48] = x + 0.25f;
	vertices[49] = z + 0.5f;
	vertices[50] = y + -0.25f;
	vertices[51] = 0.83f;
	vertices[52] = 0.70f;
	vertices[53] = 0.44f;
	vertices[54] = 5.0f;
	vertices[55] = 5.0f;

	vertices[56] = x + 0.25f;
	vertices[57] = z + 0.5f;
	vertices[58] = y + 0.25f;
	vertices[59] = 0.83f;
	vertices[60] = 0.70f;
	vertices[61] = 0.44f;
	vertices[62] = 0.0f;
	vertices[63] = 5.0f;
	*/
	vertices[0] = x + 0.f;
	vertices[1] = z + 0.0f;
	vertices[2] = y + 1.0f;
	vertices[3] = 0.83f;
	vertices[4] = 0.70f;
	vertices[5] = 0.44f;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;

	vertices[8] = x + 0.0f;
	vertices[9] = z + 0.0f;
	vertices[10] = y + 0.0f;
	vertices[11] = 0.83f;
	vertices[12] = 0.70f;
	vertices[13] = 0.44f;
	vertices[14] = 5.0f;
	vertices[15] = 0.0f;

	vertices[16] = x + 1.0f;
	vertices[17] = z + 0.0f;
	vertices[18] = y + 0.0f;
	vertices[19] = 0.83f;
	vertices[20] = 0.70f;
	vertices[21] = 0.44f;
	vertices[22] = 5.0f;
	vertices[23] = 5.0f;

	vertices[24] = x + 1.0f;
	vertices[25] = z + 0.0f;
	vertices[26] = y + 1.0f;
	vertices[27] = 0.83f;
	vertices[28] = 0.70f;
	vertices[29] = 0.44f;
	vertices[30] = 0.0f;
	vertices[31] = 5.0f;

	vertices[32] = x + 0.0f;
	vertices[33] = z + 1.0f;
	vertices[34] = y + 1.0f;
	vertices[35] = 0.83f;
	vertices[36] = 0.70f;
	vertices[37] = 0.44f;
	vertices[38] = 0.0f;
	vertices[39] = 0.0f;

	vertices[40] = x + 0.0f;
	vertices[41] = z + 1.0f;
	vertices[42] = y + 0.0f;
	vertices[43] = 0.83f;
	vertices[44] = 0.70f;
	vertices[45] = 0.44f;
	vertices[46] = 5.0f;
	vertices[47] = 0.0f;

	vertices[48] = x + 1.0f;
	vertices[49] = z + 1.0f;
	vertices[50] = y + 0.0f;
	vertices[51] = 0.83f;
	vertices[52] = 0.70f;
	vertices[53] = 0.44f;
	vertices[54] = 5.0f;
	vertices[55] = 5.0f;

	vertices[56] = x + 1.0f;
	vertices[57] = z + 1.0f;
	vertices[58] = y + 1.0f;
	vertices[59] = 0.83f;
	vertices[60] = 0.70f;
	vertices[61] = 0.44f;
	vertices[62] = 0.0f;
	vertices[63] = 5.0f;

	// Indices for vertices order
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	indices[6] = 4;
	indices[7] = 5;
	indices[8] = 6;

	indices[9] = 4;
	indices[10] = 6;
	indices[11] = 7;

	indices[12] = 0;
	indices[13] = 7;
	indices[14] = 3;

	indices[15] = 0;
	indices[16] = 4;
	indices[17] = 7;

	indices[18] = 3;
	indices[19] = 6;
	indices[20] = 2;

	indices[21] = 3;
	indices[22] = 7;
	indices[23] = 6;

	indices[24] = 1;
	indices[25] = 6;
	indices[26] = 2;

	indices[27] = 1;
	indices[28] = 5;
	indices[29] = 6;

	indices[30] = 1;
	indices[31] = 0;
	indices[32] = 4;

	indices[33] = 1;
	indices[34] = 4;
	indices[35] = 5;

	/*
	// Generates Vertex Array Object and binds it
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO1(indices, sizeof(indices));


	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	*/
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
