#include "UpdatePacket.h"

UpdatePacket::UpdatePacket(glm::vec3 targetBlock, int chunkX, int chunkY)
{
	this->targetBlock = targetBlock;
	this->chunkX = chunkX;
	this->chunkY = chunkY;
}

int UpdatePacket::getChunkX()
{
	return chunkX;
}

int UpdatePacket::getChunkY()
{
	return chunkY;
}

glm::vec3 UpdatePacket::getTargetBlock()
{
	return targetBlock;
}
