#pragma once
#include <BWAPI.h>
#include "InformationManager.h"

using namespace BWAPI;

namespace SquadT{
	enum SquadType{
		None,
		Scout,
		Protected,
		Attack,
		Produce,
		Build,
		Gather
	};
}

class Squad{
protected:
	SquadT::SquadType _type;
	Unitset _units;
	int _count;
public:
	Squad();
	void setType(SquadT::SquadType);
	SquadT::SquadType getType();
	void addUnit(Unit &);
	void removeUnit();
	Unitset & getUnits();
	void setUnits(Unitset &);
	int getCount();
	virtual void doSomething(InformationManager &) = 0;
	void update();
};