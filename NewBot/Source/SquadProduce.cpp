#include "SquadProduce.h"
#include <stdlib.h>

void SquadProduce::doSomething(InformationManager & info){
	int count = 0;
	for (auto & u : Broodwar->self()->getUnits())
		if (u->getType() == UnitTypes::Terran_SCV) count++;

	for (auto & u : _units){
		if (u->isIdle() && u->getType() == UnitTypes::Terran_Command_Center){
			if (count <= 15) u->train(UnitTypes::Terran_SCV);
		}
	}

	if (info._strategy.getStrategyName() == "Zerg"){		
		for (auto & u : _units){
			if (u->isIdle() && u->getType() == UnitTypes::Terran_Barracks){				
				u->train(UnitTypes::Terran_Marine);														
			}		
		}
	}
	else if (info._strategy.getStrategyName() == "Terran"){
		int _numFactory = 0;
		for (auto & u : _units){
			if (u->isIdle() && u->getType() == UnitTypes::Terran_Barracks){				
				u->train(UnitTypes::Terran_Marine);				
			}
			if (u->isIdle() && u->getType() == UnitTypes::Terran_Factory){

				if (_numFactory == 0){
					u->train(UnitTypes::Terran_Vulture);
					_numFactory++;
				}
				else{
					if (!info._have[UnitTypes::Terran_Machine_Shop]){
						u->train(UnitTypes::Terran_Machine_Shop);
					}
					else{
						u->train(UnitTypes::Terran_Siege_Tank_Siege_Mode);
					}
				}
			}		
		}
	}
	else if (info._strategy.getStrategyName() == "Protoss"){
		for (auto & u : _units){
			if (u->isIdle() && u->getType() == UnitTypes::Terran_Barracks){
				u->train(UnitTypes::Terran_Marine);
			}
			if (u->isIdle() && u->getType() == UnitTypes::Terran_Factory){				
				if (!info._have[UnitTypes::Terran_Machine_Shop]){
					u->train(UnitTypes::Terran_Machine_Shop);
				}
				else{
					if (rand() % 2 == 0) {
						u->train(UnitTypes::Terran_Siege_Tank_Tank_Mode);
					}
					else{
						u->train(UnitTypes::Terran_Siege_Tank_Siege_Mode);
					}
				}
			}			
		}
	}
}