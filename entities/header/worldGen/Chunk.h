#pragma once
#include "header/Block.h"
#include <vector>

class Chunk
{
private:
	Block* BlocksArray[16][16][16];
	std::vector<Block*> BlocksVec;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	
	int numBlocks;
	int posX;
	int posY;
	
public:
	Chunk(int xID, int yID);
	void addBlock(Block* newBlock, int x, int y, int z);
	int getNumBlocks();

	//If loaded get decompressed verts and inds
	std::vector<GLfloat> getVerts();;
	std::vector<GLuint> getInds();

	// If not loaded, get compressed verts and inds.
	// Compression algorithim should only get verticies of top level blocks, side blocks, and bottom blocks.
	std::vector<GLfloat> getCompressedVerts();
	std::vector<GLuint> getCompressedInds();


};

