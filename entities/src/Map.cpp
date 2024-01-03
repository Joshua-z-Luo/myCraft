#include "header/Map.h"

Map::Map(int chunk)
{
	numChunks = chunk;
	length = chunk * 16;
	width = chunk * 16;
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

void Map::addBlockToChunk(Block* newBlock, int xID, int yID)
{

}



/*
addChunk should be called whenever the player enters a new Chunk.
TODO :: NEED TO UPDATE PLAYER POSITION ON INSERTION
*/
void Map::addChunk(int code)
{
	
	if (code == 0) {
		//inital generation
		for (int x = 0; x < 3; x++) {
			// Stored on heap
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			for (int y = 0; y < 3; y++) {
				// Stored on heap
				Chunk * newChunk = new Chunk(1, 1);
				temp->push_back(newChunk);
				numChunks += 1;
			}
			ChunksArray.push_back(temp);
		}
	}
	else {
		// check if border or border corner
		if (playerChunkX == 0 && playerChunkY == 0) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}
				
			}

			// Then insert into array
			ChunksArray.insert(ChunksArray.begin(), temp);

			// add top rows
			for (int i = 1; i < ChunksArray.size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}

			}
			
		}
		else if (playerChunkX == ChunksArray.size() && playerChunkY == 0) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}

			// Then insert into array
			ChunksArray.insert(ChunksArray.end(), temp);

			// add top rows
			for (int i = 0; i < ChunksArray.size() - 1; i++) {
				if (i >= ChunksArray.size() - 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}

			}

		}
		else if (playerChunkY == ChunksArray[0]->size() && playerChunkX == 0) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i >= 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}

			// Then insert into array
			ChunksArray.insert(ChunksArray.begin(), temp);

			// add top rows
			for (int i = 1; i < ChunksArray.size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->end(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->end(), nullptr);
				}

			}

		}
		else if (playerChunkY == ChunksArray[0]->size() && playerChunkX == ChunksArray.size()) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i >= 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}

			// Then insert into array
			ChunksArray.insert(ChunksArray.end(), temp);

			// add top rows
			for (int i = 0; i < ChunksArray.size() - 1; i++) {
				if (i >= ChunksArray.size() - 3) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->end(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->end(), nullptr);
				}

			}

		}
		else if (playerChunkX == 0) {
			// Non corner boundries
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i - 1 <= playerChunkY <= i + 1) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}
			ChunksArray.insert(ChunksArray.begin(), temp);
		}
		else if (playerChunkY == 0) {
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i - 1 <= playerChunkX <= i + 1) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}
			}

		}
		else if (playerChunkX == ChunksArray.size()) {
			// Non corner boundries
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i - 1 <= playerChunkY <= i + 1) {
					Chunk* insertChunk = new Chunk(1, 1);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}
			ChunksArray.insert(ChunksArray.begin(), temp);
		}
		else if (playerChunkY == ChunksArray[0]->size()) {
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i - 1 <= playerChunkX <= i + 1) {
					Chunk* insertChunk = new Chunk(1, 1);
					ChunksArray[i]->insert(ChunksArray[i]->end(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->end(), nullptr);
				}
			}
		}
		else {
			// NOT A BOUNDARY
			for (int x = playerChunkX - 1; x <= playerChunkX + 1; x++) {
				for (int y = playerChunkY - 1; y <= playerChunkX + 1; y++) {
					if ((*ChunksArray[x])[y] == nullptr) {
						(*ChunksArray[x])[y] = new Chunk(1, 1);
						numChunks += 1;
					}
				}
			}
		}
	}
	// CHECK IF PLAYER IS ON A BOUNDRY CHUNK, THEN SEARCH THE 9 CHUNKS AROUND THEM TO SEE WHICH CHUNKS NEED TO BE CREATED


}

void Map::generateRandomMap()
{
	this->genHeightMap();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			GLfloat temp = heightMap[x][y];
			Block block(x, y, temp);
			addBlock(&block);
		}
	}
}

void Map::playerPosition(int newX, int newY)
{
	// KEEP THIS UPDATED SO WE CAN DETERMINE WHICH CHUNKS TO LOAD AND WHICH TO DELOAD FROM ChunksArray
	playerChunkX = newX;
	playerChunkY = newY;
}

int Map::getNumChunks()
{
	return numChunks;
}

void Map::genHeightMap()
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
		}
	}
}


