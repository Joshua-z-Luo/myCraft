#include "header/Map.h"

Map::Map(int chunk)
{
	numChunks = 0;
	length = chunk * Constants::CHUNK_SIZE;
	width = chunk * Constants::CHUNK_SIZE;
	numBlocks = 0;
	heightMap = new GLfloat * [length];
	originX = 1;
	originY = 1;
	playerChunkX = 1;
	playerChunkY = 1;
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


/*
Adds a block the the specified chunk.
*/
void Map::addBlockToChunk(int xID, int yID, int x, int y, int z, int id)
{
	// xID + originX, yID + originY IS NOT THE CORRECT CALCULATION (NEEDS TO BE FIXED)
	(*ChunksArray[xID + originX])[yID + originY]->addBlock(id, x, y, z);
}

void Map::removeBlockFromChunk(int xID, int yID, int x, int y, int z)
{	
	if (x < 0) {
		x = Constants::CHUNK_SIZE + (x % (Constants::CHUNK_SIZE));
	}
	else {
		x = x % Constants::CHUNK_SIZE;
	}
	if (y < 0) {
		y = Constants::CHUNK_SIZE + (y % (Constants::CHUNK_SIZE));
		
	}
	else {
		y = y % Constants::CHUNK_SIZE;
	}
	if (x == 32) {
		x = 0;
	}
	if (y == 32) {
		y = 0;
	}
	// xID + originX, yID + originY IS NOT THE CORRECT CALCULATION (NEEDS TO BE FIXED)
	// Currently using maps check of player position to find chunk to remove block
	// needs to depend on given xID, yID instead for extendability of method.

	fprintf(stdout, " remove: x: %d y: %d \n", x, y);
	(*ChunksArray[playerChunkX])[playerChunkY]->removeBlock(x, y, z);
}

/*
Helper function for addChunk. Fills given empty chunk with blocks.
*/
void Map::populateChunk(Chunk * chunk, int xID, int yID)
{
	this->genHeightMap(xID, yID);
	for (int x = 0; x < Constants::CHUNK_SIZE; x++) {
		for (int y = 0; y < Constants::CHUNK_SIZE; y++) {
			chunk->addBlock(1, x, y, heightMap[x][y]);
		}
	}
}


/*
Loads the chunks in loadOrder on map creation.
*/
void Map::loadMap()
{
	// should be called on start after addChunks
	for (int i = 0; i < 9; i++) {
		std::vector<compBlock * > temp = loadOrder[i]->getBlocks();
		for (int id = 0; id < temp.size(); id++) {
			Block block(temp[id]->x, temp[id]->y, temp[id]->z);
			addBlock(&block);
		}
	} 
}

/*
Updates the loadOrder, verticies, and indicies with the chunks that should currently be loaded.

CURRENTLY WE REMOVE EVERYTHING FROM THE LOADORDER/VERTS/INDS AND THEN ADD THE NEW CHUNK DATA.
SHOULD BE OPTIMIZED TO KEEP CHUNK DATA THAT CAN BE RECYCLED, SINCE MOVEMENT IS PREDICTABLE. 
*/
void Map::updateMap(int oldX, int oldY)
{
	BlocksVec.clear();
	indices.clear();
	vertices.clear();
	loadOrder.clear();
	numBlocks = 0;
	for (int x = playerChunkX - 1; x <= playerChunkX + 1; x++) {
		for (int y = playerChunkY - 1; y <= playerChunkY + 1; y++) {
			std::vector<compBlock* > temp = (*ChunksArray[x])[y]->getBlocks();
			loadOrder.push_back((*ChunksArray[x])[y]);
			for (int id = 0; id < temp.size(); id++) {
				Block block(temp[id]->x, temp[id]->y, temp[id]->z);
				addBlock(&block);
			}
		}
	}

}



/*
addChunk should be called whenever the player enters a new Chunk.
TODO :: NEED TO UPDATE PLAYER POSITION ON INSERTION
REMEMBER PLAYER POSITION IS BASED ON POSITION WITH IN CHUNKARRAY NOT RELATIVE TO ORIGIN
*/
void Map::addChunk(int code)
{
	
	if (code == 0) {
		//inital generation
		for (int x = -1; x < 2; x++) {
			// Stored on heap
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			for (int y = -1; y < 2; y++) {
				// Stored on heap
				Chunk * newChunk = new Chunk(x, y);
				populateChunk(newChunk, x, y);
				temp->push_back(newChunk);
				loadOrder.push_back(newChunk);

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
				if (i < 2) {
					Chunk* insertChunk = new Chunk(0 - originX - 1, i - originY);
					populateChunk(insertChunk, 0 - originX - 1, i - originY);
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
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(-1 - originX + i, 0 - originY - 1);
					populateChunk(insertChunk, -1 - originX + i, 0 - originY - 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}

			}
			playerChunkX += 1;
			playerChunkY += 1;
			originX += 1;
			originY += 1;
			
		}
		else if (playerChunkX == ChunksArray.size() - 1 && playerChunkY == 0) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i < 2) {
					Chunk* insertChunk = new Chunk(ChunksArray.size() - originX, i - originY);
					populateChunk(insertChunk, ChunksArray.size() - originX, i - originY);
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
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i >= ChunksArray.size() - 3) {
					Chunk* insertChunk = new Chunk(i - originX, 0 - originY - 1);
					populateChunk(insertChunk, i - originX, 0 - originY - 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}

			}
			playerChunkY = 1;
			originY += 1;

		}
		else if (playerChunkY == ChunksArray[0]->size() - 1 && playerChunkX == 0) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i > ChunksArray[0]->size() - 3) {
					Chunk* insertChunk = new Chunk(0 - originX - 1, i - originY);
					populateChunk(insertChunk, 0 - originX - 1, i - originY);
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
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i < 3) {
					Chunk* insertChunk = new Chunk(-1 - originX + i, ChunksArray[i]->size() - originY);
					populateChunk(insertChunk, -1 - originX + i, ChunksArray[i]->size() - originY);
					ChunksArray[i]->insert(ChunksArray[i]->end(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->end(), nullptr);
				}

			}
			playerChunkX = 1;
			originX += 1;

		}
		else if (playerChunkY == ChunksArray[0]->size() - 1 && playerChunkX == ChunksArray.size() - 1) {
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			// Created new row/col of chunk at corner
			// fill row and col with Chunks locally, and nullptrs for filler.
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (i > ChunksArray[0]->size() - 3) {
					Chunk* insertChunk = new Chunk(ChunksArray.size() - originX, i - originY);
					populateChunk(insertChunk, ChunksArray.size() - originX, i - originY);
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
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (i >= ChunksArray.size() - 3) {
					Chunk* insertChunk = new Chunk(i - originX, ChunksArray[0]->size() - originY);
					populateChunk(insertChunk, i - originX, ChunksArray[0]->size() - originY);
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
				if (playerChunkY - 1 <= i && i <= playerChunkY + 1) {
					Chunk* insertChunk = new Chunk( playerChunkX - originX - 1, i - originY);
					populateChunk(insertChunk, playerChunkX - originX - 1, i - originY);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}
			playerChunkX += 1;
			originX += 1;
			ChunksArray.insert(ChunksArray.begin(), temp);
		}
		else if (playerChunkY == 0) {
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (playerChunkX - 1 <= i && i <= playerChunkX + 1) {
					Chunk* insertChunk = new Chunk(i - originX, playerChunkY - originY - 1);
					populateChunk(insertChunk, i - originX, playerChunkY - originY - 1);
					ChunksArray[i]->insert(ChunksArray[i]->begin(), insertChunk);
					numChunks += 1;
				}
				else {
					ChunksArray[i]->insert(ChunksArray[i]->begin(), nullptr);
				}
			}
			playerChunkY += 1;
			originY += 1;

		}
		else if (playerChunkX == ChunksArray.size() - 1) {
			// Non corner boundries
			std::deque<Chunk*>* temp = new std::deque<Chunk*>;
			for (int i = 0; i < ChunksArray[0]->size(); i++) {
				if (playerChunkY - 1 <= i && i <= playerChunkY + 1) {
					Chunk* insertChunk = new Chunk(playerChunkX - originX + 1, i - originY);
					populateChunk(insertChunk, playerChunkX - originX + 1, i - originY);
					temp->push_back(insertChunk);
					numChunks += 1;
				}
				else {
					temp->push_back(nullptr);
				}

			}
			ChunksArray.insert(ChunksArray.end(), temp);
			
		}
		else if (playerChunkY == ChunksArray[0]->size() - 1) {
			for (int i = 0; i < ChunksArray.size(); i++) {
				if (playerChunkX - 1 <= i && i <= playerChunkX + 1) {
					Chunk* insertChunk = new Chunk(i - originX, playerChunkY - originY + 1);
					populateChunk(insertChunk, i - originX, playerChunkY - originY + 1);
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
				for (int y = playerChunkY - 1; y <= playerChunkY + 1; y++) {
					if ((*ChunksArray[x])[y] == nullptr) {
						Chunk * insertChunk = new Chunk(x - originX, y - originY );
						populateChunk(insertChunk, x - originX, y - originY);
						(*ChunksArray[x])[y] = insertChunk;
						numChunks += 1;
					}
				}
			}
		}
	}
	// CHECK IF PLAYER IS ON A BOUNDRY CHUNK, THEN SEARCH THE 9 CHUNKS AROUND THEM TO SEE WHICH CHUNKS NEED TO BE CREATED


}

void Map::printChunks()
{

	// FOR DEBUG PURPOSES
	for (int x = 0; x < ChunksArray.size(); x++) {
		for (int y = 0; y < ChunksArray[x]->size(); y++) {
			if ((*ChunksArray[x])[y] != nullptr) {
				fprintf(stdout, "| %d %d", (*ChunksArray[x])[y]->posX, (*ChunksArray[x])[y]->posY);
			}
			else {
				fprintf(stdout, "| N N");
			}
		}
		fprintf(stdout, "\n");
		
	}
	fprintf(stdout, "%d %d \n", playerChunkX, playerChunkY);

	fprintf(stdout, "END \n");

}

void Map::playerPosition(int newX, int newY)
{
	// REMEBER THAT THE playerChunk variables are the players position WITHIN THE DEQUE OF CHUNKS
	// KEEP THIS UPDATED SO WE CAN DETERMINE WHICH CHUNKS TO LOAD AND WHICH TO DELOAD FROM ChunksArray
	playerChunkX = newX;
	playerChunkY = newY;
}

void Map::playerPositionCord(int newX, int newY)
{ 
	// USES PLAYER COORDINATES RATHER THEN PLAYER POSITION IN CHUNKSARRAY

	playerChunkX = originX + newX;
	playerChunkY = originY + newY;

}

int Map::getNumChunks()
{
	return numChunks;
}

/*
Returns all the triangles within the player chunk. Used for ray casting.
Resulting vector is formatted such that, every 37 indicies is a block. 
First index of each 36 is the position of the block in the world, while the last 36 are its vertex positions.
*/
std::vector<glm::vec3> Map::getPlayerChunk()
{
	std::vector<glm::vec3> result;
	std::vector<compBlock *> temp = (*ChunksArray[playerChunkX])[playerChunkY]->getBlocks();
	for (int i = 0; i < temp.size(); i++) {
		Block block(temp[i]->x, temp[i]->y, temp[i]->z);
		result.push_back(glm::vec3(temp[i]->x, temp[i]->y, temp[i]->z));
		glm::vec3 * array = block.getTriangles();
		for (int num = 0; num < 36; num++) {
			result.push_back(array[num]);
		}
		delete[] array;
	}
	return result;
}

void Map::genHeightMap(int xCord, int yCord)
{
	for (int x = 0; x < Constants::CHUNK_SIZE; x++) {
		for (int y = 0; y < Constants::CHUNK_SIZE; y++) {

			// Audjust noise values (the amount x, y is divided by below)
			// Higher -> more variation, lower -> less
			// Simplex Noise Algo implemented via GLM
			GLfloat heightV = glm::simplex(glm::vec2{ (x + (Constants::CHUNK_SIZE * xCord)) / 64.0f, (y + (Constants::CHUNK_SIZE * yCord)) / 64.0f });
			heightV += 1;
			heightV /= 2;
			heightV *= 16;
			heightMap[x][y] = heightV;
		}
	}

	
}


