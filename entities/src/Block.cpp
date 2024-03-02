#include "header/Block.h"


Block::Block(GLfloat x, GLfloat y, GLfloat z, int id)
{
	this->id = id;
	z = round(z);
	this->x = x;
	this->y = y;
	this->z = z;
	for (auto& baseVertex : baseVertices) {
		baseVertex.position += glm::vec3(x, z, y);
	}


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

int Block::getID()
{
	return id;
}
glm::vec3 Block::getBlockCords()
{
	//fprintf(stdout, "%f %f %f \n", this->x, this->y, this->z);
	return glm::vec3(this->x, this->y, this->z);
}

Vertex* Block::getVert()
{
	return baseVertices;
}

GLuint* Block::getInd()
{
	return indices;
}

Triangle * Block::getTriangles()
{
	//glm::vec3* result = new glm::vec3[36];
	Triangle * result = new Triangle[12];
	for (int i = 0; i < 12; i++) {
		/*
		for (int x = i * 3; x < (i * 3) + 3; x++) {

			

			glm::vec3 temp(baseVertices[(indices[x])].position.x, baseVertices[(indices[x])].position.y, baseVertices[(indices[x])].positSion.z);
			//result[x] = temp;
		}*/


		glm::vec3 temp1(baseVertices[(indices[i * 3])].position.x, baseVertices[(indices[i * 3])].position.y, baseVertices[(indices[i * 3])].position.z);
		glm::vec3 temp2(baseVertices[(indices[(i * 3) + 1])].position.x, baseVertices[(indices[(i * 3) + 1])].position.y, baseVertices[(indices[(i * 3) + 1])].position.z);
		glm::vec3 temp3(baseVertices[(indices[(i * 3) + 2])].position.x, baseVertices[(indices[(i * 3) + 2])].position.y, baseVertices[(indices[(i * 3) + 2])].position.z);
		Triangle triangle(glm::vec3(x, y, z), temp1, temp2, temp3);
		result[i] = triangle;
	}
	return result;
}

void Block::createMesh(Texture * texture[2])
{
	std::vector <Vertex> verts(baseVertices, baseVertices + sizeof(baseVertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(*texture, *texture + sizeof(&texture) / sizeof(Texture));
	mesh = std::make_unique<Mesh>(verts, ind, tex);
}

void Block::drawMesh(Shader& shader, Player& camera)
{
	mesh->Draw(shader, camera);
}
