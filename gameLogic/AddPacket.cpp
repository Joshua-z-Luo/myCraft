#include "AddPacket.h"

AddPacket::AddPacket(glm::vec3 targetBlock)
{
	this->targetBlock = targetBlock;
	this->actionID = 2;
}

glm::vec3 AddPacket::conductAction()
{
	return targetBlock;

}