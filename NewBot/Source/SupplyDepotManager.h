#pragma once
#include <BWAPI.h>
#include "InformationManager.h"

using namespace BWAPI;

class SupplyDepotManager{
	int lastBuild;
	Unit _unit;
public:	
	SupplyDepotManager();
	Unit & getUnit();
	void doSomething(InformationManager &);
	void buildOne(InformationManager &);
};