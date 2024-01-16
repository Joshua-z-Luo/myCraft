#pragma once

#include "header/Block.h"
#include "header/worldGen/Chunk.h"
#include "header/worldGen/compBlock.h"
#include <glm/gtc/noise.hpp>
#include <vector>
#include "tuple"
#include "deque"
#include "../../constants.h"
#include <cstdlib>



class Map
{
private:
	// To be moved to chunk
	std::vector<Block*> BlocksVec;
	int numBlocks;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	std::deque<std::deque<Chunk*>*> ChunksArray;

	std::deque<Chunk*> loadOrder; 
	// store chunk pointers
	// this could be a raw array, since it technically can always remain the same size ( only 9 chunks are ever loaded at one time )
	

	int length;
	int width;
	int numChunks;

	GLfloat ** heightMap;
	void genHeightMap(int xCord, int yCord);

	int playerChunkX;
	int playerChunkY;
	int originX;
	int originY;


public:
	Map(int chunk);

	void playerPosition(int newX, int newY);
	void playerPositionCord(int newX, int newY);

	int getNumBlocks();

	void addBlock(Block* newBlock);
	void addBlockToChunk(int xID, int yID, int x, int y, int z, int id);
	void removeBlockFromChunk(int xID, int yID, int x, int y, int z);
	void populateChunk(Chunk * chunk, int xID, int yID);

	void loadMap();
	void updateMap(int oldX, int oldY);

	void addChunk(int code);

	void printChunks();

	std::vector<GLfloat> getVerts();;
	std::vector<GLuint> getInds();
	int getNumChunks();

	std::vector<glm::vec3> getPlayerChunk();
	std::vector<glm::vec3> getBlockCordinates();

};

