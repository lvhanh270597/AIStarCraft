#pragma once
#include "BuildOrderManager.h"
#include <BWAPI.h>

using namespace BWAPI;
using namespace UnitTypes;

BuildOrderManager::BuildOrderManager(){

	_isAssigned = false;

	deque <UnitType> _que;	

	_que.push_back(UnitTypes::Terran_Barracks);
	_need[Terran_Marine] = deque<UnitType>(_que);

	_que.pop_front();
	_que.push_back(Terran_Refinery);
	_que.push_back(Terran_Barracks);
	_need[Terran_Medic] = deque<UnitType>(_que);
	_need[Terran_Ghost] = deque<UnitType>(_que);
	_need[Terran_Machine_Shop] = deque<UnitType>(_que);
		

	for (int i = 0; i < 4; i++) _buildings.push_back(Terran_Barracks);
	_buildings.push_back(Terran_Command_Center);
	_buildings.push_back(Terran_Barracks);

	UnitType arr1[] = { Terran_Barracks, Terran_Refinery, Terran_Academy, Terran_Command_Center };
	for (int i = 0; i < 4; i++) _buildZerg.push_back(arr1[i]);

	UnitType arr2[] = { Terran_Refinery, Terran_Factory, Terran_Factory };
	for (int i = 0; i < 3; i++) _buildTerran.push_back(arr2[i]);

	UnitType arr3[] = { Terran_Refinery, Terran_Factory, Terran_Command_Center };
	for (int i = 0; i < 3; i++) _buildProtoss.push_back(arr3[i]);
}

deque<UnitType> & BuildOrderManager::getBuilding(){
	return _buildings;
}

void BuildOrderManager::update(StrategyManager & _strategy, map<UnitType, bool> & _have){

	if (!_isAssigned){
		for (auto & e : Broodwar->enemy()->getUnits()){
			// Nếu đối thủ là Zerg thì chiến thuật với Zerg
			if (e->getType() == UnitTypes::Zerg_Hatchery){
				_isAssigned = true;
				_strategy.getStrategyName() = "Zerg";
				Broodwar->sendText("Strategy with Zerg");
				for (int i = 0; i < _buildZerg.size(); i++)
					_buildings.push_back(_buildZerg[i]);
			}
			// Nếu đối thủ là Terran
			if (e->getType() == UnitTypes::Terran_Command_Center){
				_isAssigned = true;
				Broodwar->sendText("Strategy with Terran");
				_strategy.getStrategyName() = "Terran";
				for (int i = 0; i < _buildTerran.size(); i++)
					_buildings.push_back(_buildTerran[i]);
			}
			if (e->getType() == UnitTypes::Protoss_Nexus){
				_isAssigned = true;
				Broodwar->sendText("Strategy with Protoss");
				_strategy.getStrategyName() = "Protoss";
				for (int i = 0; i < _buildProtoss.size(); i++)
					_buildings.push_back(_buildProtoss[i]);
			}
		}
	}

	// Nếu chưa xây dựng xong mục tiêu cũ, thì phải xây dựng cho xong đã	
	// Nếu số quân nhiều phải xây dựng thêm Supply depot	

	//

	/*if (_strategy.getBuildCharacters().empty()) return; 	

	bool ok = false;
	UnitType & target = _strategy.getBuildCharacters().front();
	for (int i = 0; i < _need[target].size(); i++){
		UnitType needi = _need[target][i];
		if (!_have[needi]){
			ok = true;
			_buildings.push_back(needi); 
		}
	}
	if (!ok) _strategy.getBuildCharacters().pop_front();	
	*/
}
