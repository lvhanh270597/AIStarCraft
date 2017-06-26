#include "SquadBuild.h"
#include <BWAPI.h>

using namespace Filter;

SquadBuild::SquadBuild(){
	isBuilding = false;
	countFrames = 0;
	target = UnitTypes::None;
}

char *change(UnitType u){
	if (u == UnitTypes::Terran_Barracks) return "Barracks";
	if (u == UnitTypes::Terran_Supply_Depot) return "Supply Depot";
	if (u == UnitTypes::Terran_Refinery) return "Refinery";
	if (u == UnitTypes::Terran_Academy) return "Academy";
	if (u == UnitTypes::Terran_Command_Center) return "Command Center";
	if (u == UnitTypes::Terran_Factory) return "Factory";
	return "Unknown";
}

void SquadBuild::doSomething(InformationManager & info){
	if (Broodwar->getFrameCount() == 0){
		for (auto & u : _units)
			if (u->isIdle()) u->gather(u->getClosestUnit(Filter::IsMineralField));
	}

	if (isBuilding){		
		countFrames--;
		if (countFrames < 0){			
			Broodwar->sendText("Xong nhiem vu");
			Broodwar->sendText(change(info._buildOrder.getBuilding().front()));
			isBuilding = false;
			info._buildOrder.getBuilding().pop_front();
		}
	}

	if (!info._buildOrder.getBuilding().empty() && !isBuilding){
		target = info._buildOrder.getBuilding().front();
		UnitType & _macro = target;
		if (Broodwar->self()->minerals() >= _macro.mineralPrice() + 52 && Broodwar->self()->gas() >= _macro.gasPrice()){
			for (auto & u : _units){
				if (u->isIdle() || u->isCarryingGas() || u->isCarryingMinerals()){
					Broodwar->sendText(change(target));
					if (_macro != UnitTypes::Terran_Command_Center)
					{
						TilePosition targetBuildLocation = Broodwar->getBuildLocation(_macro, info._baseSelfLocation->getTilePosition());
						if (targetBuildLocation)
						{
							// Order the builder to construct the supply structure	
							if (u->canBuild(_macro, targetBuildLocation)){								
								while (!u->build(_macro, targetBuildLocation));
								isBuilding = true;
								count = 0;
								countFrames = _macro.buildTime() + 200;
								Broodwar->sendText("Ok. Build");															
							}
						}
					}
					else{				
						static int countTime = u->getDistance(info._nextGather) / 2;
						countTime--;
						if (countTime > 0) u->move(info._nextGather);
						else{
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(_macro, u->getTilePosition());
							if (targetBuildLocation)
							{
								// Order the builder to construct the supply structure	
								if (u->canBuild(_macro, targetBuildLocation)){
									while (!u->build(_macro, targetBuildLocation));
									isBuilding = true;
									count = 0;
									countFrames = _macro.buildTime() + 200;
									Broodwar->sendText("Ok. Build");
								}
							}
						}
					}
				}
			}
		}
	}
}
