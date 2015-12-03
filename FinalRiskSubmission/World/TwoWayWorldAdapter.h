#pragma once
#include "WorldConquest.h"
#include "WorldCustom.h"

class TwoWayFileFormatAdapter : public WorldConquest, public WorldCustom {
private:
	WorldConquest* formatConquest;
	WorldCustom* formatCustom;
public:
	TwoWayFileFormatAdapter(WorldConquest* peg)
	{
		formatConquest = NULL;
		formatCustom = new WorldCustom(peg);
	}
	TwoWayFileFormatAdapter(WorldCustom* peg)
	{
		formatConquest = new WorldConquest(peg);
		formatCustom = NULL;
	}
	bool fromFile() {
		if (formatConquest)
			return formatConquest->fromFile();
		if (formatCustom)
			return formatCustom->fromFile();
		return false;
	}
	bool toFile() {
		if (formatConquest)
			return formatConquest->toFile();
		if (formatCustom)
			return formatCustom->toFile();
		return false;
	}
};

