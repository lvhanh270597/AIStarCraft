#include "SquadGatherMin.h"

void SquadGatherMin::addUnit(Unit & u){
	_units.insert(u);
}
void SquadGatherMin::doSomething(){
	for (auto & u : _units){
		if (u->isIdle() || u->isCarryingGas()){
			u->gather(u->getClosestUnit(Filter::IsMineralField));
		}
	}
}
Unitset & SquadGatherMin::getUnits(){
	return _units;
}