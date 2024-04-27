#include "DestroyPacket.h"

DestroyPacket::DestroyPacket(glm::vec3 targetBlock)
{
	this->targetBlock = targetBlock;
	this->actionID = 1;
}

glm::vec3 DestroyPacket::conductAction()
{
	return targetBlock;
}
