#pragma once
#include <BWAPI.h>
#include "SquadScout.h"
#include "SquadGather.h"
#include "SquadProduce.h"
#include "SquadBuild.h"
#include "SupplyDepotManager.h"
#include "SquadAttack.h"

using namespace BWAPI;

class SquadManager{
	SquadScout _squadScout;
	SquadGather _squadGather;
	SquadProduce _squadProduce;
	SquadBuild _squadBuild;
	SupplyDepotManager _supplyMan;
	SquadAttack _squadAttack;
	
	std::map<Unit, SquadT::SquadType> isAssigned;
public:
	SquadManager();	
	void doSomething(InformationManager &);
	void update(InformationManager &);
	void balance(InformationManager &);
	Squad & getSquad(SquadT::SquadType);
};