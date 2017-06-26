#pragma once
#include <BWAPI.h>

using namespace BWAPI;

class SquadGatherGas{
	Unitset _units;
public:
	void addUnit(Unit &);
	void doSomething();
	Unitset & getUnits();
};