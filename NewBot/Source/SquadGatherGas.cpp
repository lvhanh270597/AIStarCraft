#include "SquadGatherGas.h"

void SquadGatherGas::addUnit(Unit & u){
	_units.insert(u);
}
void SquadGatherGas::doSomething(){
	for (auto & u : _units){
		if (u->isIdle() || u->isCarryingMinerals()){ 
			u->gather(u->getClosestUnit(Filter::IsRefinery));
		}
	}
}
Unitset & SquadGatherGas::getUnits(){
	return _units;
}