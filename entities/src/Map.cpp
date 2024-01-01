#include "header/Map.h"

Map::Map()
{
	numBlocks = 0;
}

std::vector<GLfloat> Map::getVerts()
{
	return vertices;
}

std::vector<GLuint> Map::getInds()
{

	return indices;
}

int Map::getNumBlocks()
{
	return numBlocks;
}

void Map::addBlock(Block * newBlock)
{
	BlocksVec.push_back(newBlock);
	for (int i = 0; i < 64; i++) {
		vertices.push_back(newBlock->vertices[i]);
	}
	for (int i = 0; i < 36; i++) {
		indices.push_back(newBlock->indices[i] + (8 * numBlocks));
	}
	numBlocks += 1;
}


