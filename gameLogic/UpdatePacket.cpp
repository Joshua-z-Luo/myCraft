#include "UpdatePacket.h"

UpdatePacket::UpdatePacket()
{
	actionID = 0;
}

int UpdatePacket::getActionID()
{
	return actionID;
}
