#include "AddPacket.h"

AddPacket::AddPacket(glm::vec3 targetBlock, int blockID)
{
	this->targetBlock = targetBlock;
	this->blockID = blockID;
	this->actionID = 2;
}

glm::vec3 AddPacket::conductAction()
{
	return targetBlock;

}