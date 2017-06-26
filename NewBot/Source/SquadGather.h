#pragma once
#include "Squad.h"
#include "InformationManager.h"
#include "SquadGatherGas.h"
#include "SquadGatherMin.h"

class SquadGather : public Squad{
	SquadGatherGas _squadGas;
	SquadGatherMin _squadMin;
public:
	void doSomething(InformationManager &);
	void balance();
};