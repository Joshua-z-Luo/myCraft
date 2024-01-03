#pragma once

#include "header/Block.h"
#include "header/worldGen/Chunk.h"
#include <glm/gtc/noise.hpp>
#include <vector>
#include "deque"


class Map
{
private:
	// To be moved to chunk
	std::vector<Block*> BlocksVec;
	int numBlocks;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::deque<std::deque<Chunk*>*> ChunksArray;
	int length;
	int width;
	int numChunks;
	GLfloat ** heightMap;
	void genHeightMap();

	int playerChunkX;
	int playerChunkY;

public:
	Map(int chunk);

	void playerPosition(int newX, int newY);

	// move to chunk
	void generateRandomMap();
	int getNumBlocks();

	// needs to be updateed for chunks
	void addBlock(Block* newBlock);
	void addBlockToChunk(Block* newBlock, int xID, int yID);

	void addChunk(int code);

	std::vector<GLfloat> getVerts();;
	std::vector<GLuint> getInds();
	int getNumChunks();
};

