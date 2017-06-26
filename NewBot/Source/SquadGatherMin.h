#pragma once
#include <BWAPI.h>

using namespace BWAPI;

class SquadGatherMin{
	Unitset _units;
public:
	Unitset & getUnits();
	void addUnit(Unit &);
	void doSomething();
};