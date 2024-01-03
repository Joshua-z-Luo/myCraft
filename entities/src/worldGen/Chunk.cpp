#include "header/worldGen/Chunk.h"

Chunk::Chunk(int xID, int yID)
{
	// Chunk height is: +8, -8 (16) 
	posX = xID;
	posY = yID;
	numBlocks = 0;
	
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				BlocksArray[x][y][z] = nullptr;
			}
		}
	}

}

void Chunk::addBlock(Block* newBlock, int x, int y, int z)
{
	BlocksArray[x][y][z] = newBlock;
	//BlocksVec.push_back(newBlock);
	for (int i = 0; i < 64; i++) {
		vertices.push_back(newBlock->vertices[i]);
	}
	for (int i = 0; i < 36; i++) {
		indices.push_back(newBlock->indices[i] + (8 * numBlocks));
	}
	numBlocks += 1;
}

int Chunk::getNumBlocks()
{
	return numBlocks;
}

std::vector<GLfloat> Chunk::getVerts()
{
	
	return vertices;
}

std::vector<GLuint> Chunk::getInds()
{
	return indices;
}
