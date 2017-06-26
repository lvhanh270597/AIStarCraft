#pragma once
#include "Squad.h"

class SquadBuild : public Squad{
	UnitType target;
	bool isBuilding;
	int count;
	int countFrames;
public:
	SquadBuild();
	void doSomething(InformationManager &);
	void update_info(InformationManager &);
};