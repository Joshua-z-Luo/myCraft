#pragma once

#include "header/Block.h"
#include "header/worldGen/Chunk.h"
#include <vector>


class Map
{
protected:
	std::vector<Block*> BlocksVec;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	int length;
	int width;
	int numBlocks;
	GLfloat ** heightMap;


public:
	Map(int length, int width);
	void addBlock(Block* newBlock);
	void generateRandomMap();
	void genHeightMap(int x, int y);
	std::vector<GLfloat> getVerts();;
	std::vector<GLuint> getInds();
	int getNumBlocks();
	
	// VECTOR TO STORE ALL BLOCK VERTICIES
	
};

