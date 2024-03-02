#pragma once
#include "UpdatePacket.h"
class DestroyPacket :
    public UpdatePacket
{
private:
	glm::vec3 targetBlock;
public:
	DestroyPacket(glm::vec3 targetBlock);
	glm::vec3 conductAction() override;
};

