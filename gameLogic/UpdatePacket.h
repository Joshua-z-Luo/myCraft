#include<glm/glm.hpp>

#pragma once


class UpdatePacket
{
public:
	UpdatePacket(glm::vec3 targetBlock, int chunkX, int chunkY);
	int getChunkX();
	int getChunkY();
	glm::vec3 getTargetBlock();
private:
	glm::vec3 targetBlock;
	int chunkX;
	int chunkY;
};

