#include "SquadGather.h"


void SquadGather::doSomething(InformationManager & info){	
	if (info._have[UnitTypes::Terran_Refinery]) balance();
	else{
		_squadMin.getUnits().clear();
		for (auto & u : _units){
			_squadMin.addUnit((Unit)u);
		}
	}
	_squadGas.doSomething();
	_squadMin.doSomething();
}
void SquadGather::balance(){
	_squadGas.getUnits().clear();
	_squadMin.getUnits().clear();
	int n = 0;
	for (auto & u : _units){
		n++;
	}
	int count = n / 4;
	
	for (auto & u : _units){
		if (count > 0){
			_squadGas.addUnit((Unit)u);
		}
		else{
			_squadMin.addUnit((Unit)u);
		}
		count--;
	}
}