#include "header/worldGen/Chunk.h"

Chunk::Chunk(int xID, int yID)
{
	// Chunk height is: +8, -8 (16) 
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
