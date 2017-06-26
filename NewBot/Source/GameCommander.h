#pragma once
#include "SquadManager.h"

class GameCommander{
	SquadManager _squads;	
	InformationManager _info;
public:
	GameCommander();
	InformationManager & getInfo();
	void processing(InformationManager &);	
	void update();
};