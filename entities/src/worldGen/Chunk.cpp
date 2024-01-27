#include "header/worldGen/Chunk.h"


void Chunk::createChunkMesh(Texture* texture[2])
{
	// NEED TO APPLY BETTER MESH ALGORTIHIMS (GREEDY MESH) IN FUTURE THIS IS OK FOR NOW
	// CAN REDUCE NUMBER OF VERTEXS USED
	//bfs traversal
	std::vector<Vertex> result;
	std::vector<GLuint> indicies;
	for (int x = 0; x < Constants::CHUNK_SIZE; x++) {
		for (int y = 0; y < Constants::CHUNK_SIZE; y++) {
			for (int z = 0; z < Constants::CHUNK_SIZE; z++) {
				
				if (BlocksArray[x][y][z] != -1) {
					
					std::array<bool, 6> temp = checkBlockNeighbours(x, y, z);
					Vertex baseVertices[24] = {
						// Top face 
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

						// Bottom face
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX) , 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

						// Front face
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

						// Right face
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

						// Back face
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(1.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},

						// Left face
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 0.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 0.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(0.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 0.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 1.0f)},
						{glm::vec3(0.0f + x + (Constants::CHUNK_SIZE * posX), 1.0f + z, 1.0f + y + (Constants::CHUNK_SIZE * posY)), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.83f, 0.70f, 0.44f), glm::vec2(1.0f, 0.0f)},
					};
					for (int i = 0; i < 6; i++) {
						if (temp[i] == true) {
							int start = result.size();
							indicies.push_back(start);
							indicies.push_back(start + 1);
							indicies.push_back(start + 2);
							indicies.push_back(start + 2);
							indicies.push_back(start + 3);
							indicies.push_back(start);
							for (int verts = i * 4; verts < (i * 4) + 4; verts++) {
								// might ahve a memory problem here
								result.push_back(baseVertices[verts]);
							}
						}
					}
				}
				if (x + y + z == numBlocks) {
					std::vector <Texture> tex;
					tex.push_back(*(texture)[0]);
					tex.push_back(*(texture)[1]);
					mesh = std::make_unique<Mesh>(result, indicies, tex);
					return;
				}

			}
		}
	}
	//std::vector <Texture> tex; 
	//tex.push_back(*(texture)[0]);
	//tex.push_back(*(texture)[1]);
	//fprintf(stdout, " here %s \n", tex[0].type);
	//fprintf(stdout, " here %s \n", tex[1].type);
	std::vector <Texture> tex(*texture, *texture + sizeof(&texture) / sizeof(Texture));
	mesh = std::make_unique<Mesh>(result, indicies, tex);


}

void Chunk::drawMesh(Shader& shader, Player& camera)
{
	mesh->Draw(shader, camera);
}

std::array<bool, 6> Chunk::checkBlockNeighbours(int x, int y, int z)
{

	std::array<bool, 6> result = {false, false, false, false, false, false};
	if (z + 1 >= Constants::CHUNK_SIZE) {
		result[0] = true;
	}
	else if (BlocksArray[x][y][z + 1] == -1) {
		result[0] = true;
	}

	if (z - 1 <  Constants::CHUNK_SIZE) {
		result[1] = true;
	}
	else if (BlocksArray[x][y][z - 1] == -1) {
		result[1] = true;
	}
	if (y + 1 >= Constants::CHUNK_SIZE) {
		result[2] = true;
	}
	else if ( BlocksArray[x][y + 1][z] == -1) {
		result[2] = true;
	}

	if (x + 1 >= Constants::CHUNK_SIZE) {
		result[3] = true;
	}
	else if (BlocksArray[x + 1][y][z] == -1) {
		result[3] = true;
	}
	if (x - 1 < Constants::CHUNK_SIZE) {
		result[5] = true;
	}
	else if (BlocksArray[x - 1][y][z] == -1) {
		result[5] = true;
	}

	if (y - 1 <  0) {
		result[4] = true;
	}
	else if (BlocksArray[x][y - 1][z] == -1) {
		result[4] = true;
	}
	return result;
}

Chunk::Chunk(int xID, int yID)
{
	posX = xID;
	posY = yID;
	numBlocks = 0;
	
	for (int x = 0; x < Constants::CHUNK_SIZE; x++) {
		for (int y = 0; y < Constants::CHUNK_SIZE; y++) {
			for (int z = 0; z < Constants::CHUNK_SIZE; z++) {
				BlocksArray[x][y][z] = -1;
			}
		}
	}

}

void Chunk::addBlock(int id, int x, int y, int z)
{
	
	BlocksArray[x][y][z] = id;
	numBlocks += 1;
}

void Chunk::removeBlock(int x, int y, int z)
{
	if (BlocksArray[x][y][z] == -1) {
		printf("u removed nothing \n");
	}
	else {
		printf("removed block \n");
	}
	BlocksArray[x][y][z] = -1;
	numBlocks -= 1;
}

// REPLACE TUPLE WITH SOMETHING BETTER LATTER
std::vector<compBlock *> Chunk::getBlocks()
{
	std::vector<compBlock *> temp;
	for (int x = 0; x < Constants::CHUNK_SIZE; x++) {
		for (int y = 0; y < Constants::CHUNK_SIZE; y++) {
			for (int z = 0; z < Constants::CHUNK_SIZE; z++) {
				if (BlocksArray[x][y][z] != -1) {
					compBlock* block = new compBlock(x + (Constants::CHUNK_SIZE * posX), y + (Constants::CHUNK_SIZE * posY), z, BlocksArray[x][y][z]);
					temp.push_back(block);
				}
			}
		}
	}
	return temp;
}

int Chunk::getNumBlocks()
{
	return numBlocks;
}
