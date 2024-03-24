#include<glm/glm.hpp>

#pragma once


/*
Abstract Class
*/
class UpdatePacket
{
public:
	UpdatePacket();
	virtual glm::vec3 conductAction() = 0;
	int getActionID();
	int blockID = 1;
protected:
	int actionID;

};

