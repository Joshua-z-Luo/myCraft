#pragma once
#include "header/Block.h"
#include "compBlock.h"
#include <vector>
#include "../../../constants.h"

class Chunk
{
private:
	int BlocksArray[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];
	// might be able to compress this to reduce byte size and search time
	// specifically for gathering blocks during updateMap()

	int numBlocks;
	
	
public:
	Chunk(int xID, int yID);
	void addBlock(int id, int x, int y, int z);
	void removeBlock(int x, int y, int z);
	std::vector<compBlock * > getBlocks();

	int getNumBlocks();


	int posX;
	int posY;



};



// MAP LOADS DATA FROM CHUNK, CHUNK STORES COMPRESSED DATA