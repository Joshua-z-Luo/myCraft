#pragma once

#include "header/Block.h"
#include <vector>


class Map
{
protected:
	std::vector<Block*> BlocksVec;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	int numBlocks;


public:
	Map();
	void addBlock(Block* newBlock);
	std::vector<GLfloat> getVerts();;
	std::vector<GLuint> getInds();
	int getNumBlocks();
	
	// VECTOR TO STORE ALL BLOCK VERTICIES
	
};

