#pragma once
#include "header/Block.h"
#include "compBlock.h"
#include <vector>
#include "../../../constants.h"
#include "array"
#include "../Model/Mesh.h"
class Chunk
{
private:
	int BlocksArray[Constants::CHUNK_SIZE][Constants::CHUNK_SIZE][Constants::CHUNK_SIZE];
	// might be able to compress this to reduce byte size and search time
	// specifically for gathering blocks during updateMap()

	int numBlocks;
	std::unique_ptr<Mesh> mesh;
	std::array<bool, 6> checkBlockNeighbours(int x, int y, int z);
	
public:
	void createChunkMesh(Texture* texture[2]);
	void drawMesh(Shader& shader, Player& camera);
	Chunk(int xID, int yID);
	void addBlock(int id, int x, int y, int z);
	void removeBlock(int x, int y, int z);
	std::vector<compBlock * > getBlocks();

	int getNumBlocks();


	int posX;
	int posY;



};



// MAP LOADS DATA FROM CHUNK, CHUNK STORES COMPRESSED DATA