#include "SupplyDepotManager.h"

SupplyDepotManager::SupplyDepotManager(){
	lastBuild = 100;
}
void SupplyDepotManager::doSomething(InformationManager & info){
	if (Broodwar->getFrameCount() >= lastBuild + 400 && info._numOfMicros >= info._maxOfMicros - 5){		
		buildOne(info);
	}
	else{				
		if (_unit->isIdle()){			
			info._maxOfMicros = 10;
			for (auto & u : Broodwar->self()->getUnits())
				if (u->getType() == UnitTypes::Terran_Supply_Depot) info._maxOfMicros += 8;
			_unit->gather(_unit->getClosestUnit(Filter::IsMineralField || Filter::IsRefinery));
		}
	}
}

void SupplyDepotManager::buildOne(InformationManager & info){	
	UnitType _macro = UnitTypes::Terran_Supply_Depot;
	if (Broodwar->self()->minerals() >= _macro.mineralPrice() + 100){
		Unit & u = _unit;
		if (u->isIdle() || u->isCarryingGas() || u->isCarryingMinerals()){
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(_macro, u->getTilePosition());
			if (targetBuildLocation)
			{
				if (u->canBuild(_macro, targetBuildLocation))
				{					
					while (!u->build(_macro, targetBuildLocation));
					info._maxOfMicros += 8;
					lastBuild = Broodwar->getFrameCount();					
				}
			}
		}
	}
}

Unit & SupplyDepotManager::getUnit(){
	return _unit;
}