#include "header/Block.h"
#include "../../shaders/EBO.h"
#include "../../shaders/VBO.h"
#include "../../shaders/VAO.h"


Block::Block(GLfloat x, GLfloat y, GLfloat z)
{
	z = round(z);
	vertices[0] = x - 0.5f;
	vertices[1] = z - 0.5f;
	vertices[2] = y + 0.5f;
	vertices[3] = 0.83f;
	vertices[4] = 0.70f;
	vertices[5] = 0.44f;
	vertices[6] = 0.0f;
	vertices[7] = 0.0f;

	vertices[8] = x + 0.5f;
	vertices[9] = z - 0.5f;
	vertices[10] = y + 0.5f;
	vertices[11] = 0.83f;
	vertices[12] = 0.70f;
	vertices[13] = 0.44f;
	vertices[14] = 1.0f;
	vertices[15] = 0.0f;

	vertices[16] = x + 0.5f;
	vertices[17] = z + 0.5f;
	vertices[18] = y + 0.5f;
	vertices[19] = 0.83f;
	vertices[20] = 0.70f;
	vertices[21] = 0.44f;
	vertices[22] = 1.0f;
	vertices[23] = 1.0f;

	vertices[24] = x - 0.5f;
	vertices[25] = z + 0.5f;
	vertices[26] = y + 0.5f;
	vertices[27] = 0.83f;
	vertices[28] = 0.70f;
	vertices[29] = 0.44f;
	vertices[30] = 0.0f;
	vertices[31] = 1.0f;

	// Back face
	vertices[32] = x - 0.5f;
	vertices[33] = z - 0.5f;
	vertices[34] = y - 0.5f;
	vertices[35] = 0.92f;
	vertices[36] = 0.86f;
	vertices[37] = 0.76f;
	vertices[38] = 0.0f;
	vertices[39] = 0.0f;

	vertices[40] = x + 0.5f;
	vertices[41] = z - 0.5f;
	vertices[42] = y - 0.5f;
	vertices[43] = 0.92f;
	vertices[44] = 0.86f;
	vertices[45] = 0.76f;
	vertices[46] = 1.0f;
	vertices[47] = 0.0f;

	vertices[48] = x + 0.5f;
	vertices[49] = z + 0.5f;
	vertices[50] = y - 0.5f;
	vertices[51] = 0.92f;
	vertices[52] = 0.86f;
	vertices[53] = 0.76f;
	vertices[54] = 1.0f;
	vertices[55] = 1.0f;

	vertices[56] = x - 0.5f;
	vertices[57] = z + 0.5f;
	vertices[58] = y - 0.5f;
	vertices[59] = 0.92f;
	vertices[60] = 0.86f;
	vertices[61] = 0.76f;
	vertices[62] = 0.0f;
	vertices[63] = 1.0f;

	// Right face
	vertices[64] = x + 0.5f;
	vertices[65] = z - 0.5f;
	vertices[66] = y + 0.5f;
	vertices[67] = 0.76f;
	vertices[68] = 0.45f;
	vertices[69] = 0.12f;
	vertices[70] = 0.0f;
	vertices[71] = 0.0f;

	vertices[72] = x + 0.5f;
	vertices[73] = z - 0.5f;
	vertices[74] = y - 0.5f;
	vertices[75] = 0.76f;
	vertices[76] = 0.45f;
	vertices[77] = 0.12f;
	vertices[78] = 1.0f;
	vertices[79] = 0.0f;

	vertices[80] = x + 0.5f;
	vertices[81] = z + 0.5f;
	vertices[82] = y - 0.5f;
	vertices[83] = 0.76f;
	vertices[84] = 0.45f;
	vertices[85] = 0.12f;
	vertices[86] = 1.0f;
	vertices[87] = 1.0f;

	vertices[88] = x + 0.5f;
	vertices[89] = z + 0.5f;
	vertices[90] = y + 0.5f;
	vertices[91] = 0.76f;
	vertices[92] = 0.45f;
	vertices[93] = 0.12f;
	vertices[94] = 0.0f;
	vertices[95] = 1.0f;

	// Left face
	vertices[96] = x - 0.5f;
	vertices[97] = z - 0.5f;
	vertices[98] = y + 0.5f;
	vertices[99] = 0.76f;
	vertices[100] = 0.45f;
	vertices[101] = 0.12f;
	vertices[102] = 0.0f;
	vertices[103] = 0.0f;

	vertices[104] = x - 0.5f;
	vertices[105] = z - 0.5f;
	vertices[106] = y - 0.5f;
	vertices[107] = 0.76f;
	vertices[108] = 0.45f;
	vertices[109] = 0.12f;
	vertices[110] = 1.0f;
	vertices[111] = 0.0f;

	vertices[112] = x - 0.5f;
	vertices[113] = z + 0.5f;
	vertices[114] = y - 0.5f;
	vertices[115] = 0.76f;
	vertices[116] = 0.45f;
	vertices[117] = 0.12f;
	vertices[118] = 1.0f;
	vertices[119] = 1.0f;

	vertices[120] = x - 0.5f;
	vertices[121] = z + 0.5f;
	vertices[122] = y + 0.5f;
	vertices[123] = 0.76f;
	vertices[124] = 0.45f;
	vertices[125] = 0.12f;
	vertices[126] = 0.0f;
	vertices[127] = 1.0f;

	// Top face
	vertices[128] = x - 0.5f;
	vertices[129] = z + 0.5f;
	vertices[130] = y + 0.5f;
	vertices[131] = 0.67f;
	vertices[132] = 0.87f;
	vertices[133] = 0.50f;
	vertices[134] = 0.0f;
	vertices[135] = 0.0f;

	vertices[136] = x + 0.5f;
	vertices[137] = z + 0.5f;
	vertices[138] = y + 0.5f;
	vertices[139] = 0.67f;
	vertices[140] = 0.87f;
	vertices[141] = 0.50f;
	vertices[142] = 1.0f;
	vertices[143] = 0.0f;

	vertices[144] = x + 0.5f;
	vertices[145] = z + 0.5f;
	vertices[146] = y - 0.5f;
	vertices[147] = 0.67f;
	vertices[148] = 0.87f;
	vertices[149] = 0.50f;
	vertices[150] = 1.0f;
	vertices[151] = 1.0f;

	vertices[152] = x - 0.5f;
	vertices[153] = z + 0.5f;
	vertices[154] = y - 0.5f;
	vertices[155] = 0.67f;
	vertices[156] = 0.87f;
	vertices[157] = 0.50f;
	vertices[158] = 0.0f;
	vertices[159] = 1.0f;

	// Bottom face
	vertices[160] = x - 0.5f;
	vertices[161] = z - 0.5f;
	vertices[162] = y + 0.5f;
	vertices[163] = 0.98f;
	vertices[164] = 0.76f;
	vertices[165] = 0.45f;
	vertices[166] = 0.0f;
	vertices[167] = 0.0f;

	vertices[168] = x + 0.5f;
	vertices[169] = z - 0.5f;
	vertices[170] = y + 0.5f;
	vertices[171] = 0.98f;
	vertices[172] = 0.76f;
	vertices[173] = 0.45f;
	vertices[174] = 1.0f;
	vertices[175] = 0.0f;

	vertices[176] = x + 0.5f;
	vertices[177] = z - 0.5f;
	vertices[178] = y - 0.5f;
	vertices[179] = 0.98f;
	vertices[180] = 0.76f;
	vertices[181] = 0.45f;
	vertices[182] = 1.0f;
	vertices[183] = 1.0f;

	vertices[184] = x - 0.5f;
	vertices[185] = z - 0.5f;
	vertices[186] = y - 0.5f;
	vertices[187] = 0.98f;
	vertices[188] = 0.76f;
	vertices[189] = 0.45f;
	vertices[190] = 0.0f;
	vertices[191] = 1.0f;


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
