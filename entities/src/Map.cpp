#include "header/Map.h"
#include <glm/gtc/noise.hpp>

Map::Map(int length, int width)
{
	this->length = length;
	this->width = width;
	numBlocks = 0;
	heightMap = new GLfloat * [length];
	for (int i = 0; i < width; i++) {
		heightMap[i] = new GLfloat[width];
	}
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

void Map::generateRandomMap()
{
	this->genHeightMap(0, 0);
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			GLfloat temp = heightMap[x][y];
			Block block(x, y, temp);
			addBlock(&block);
		}
	}
}

void Map::genHeightMap(int x, int y)
{
	// loop through each position in map
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {

			// Audjust noise values (the amount x, y is divided by below)
			// Higher -> more variation, lower -> less
			// Simplex Noise Algo implemented via GLM
			GLfloat heightV = glm::simplex(glm::vec2{ x / 64.0f, y / 64.0f});
			heightV += 1;
			heightV /= 2;
			heightV *= 16;
			heightMap[x][y] = heightV;
			fprintf(stdout, "%f", heightMap[x][y]);
		}
	}
}


