#include "InformationManager.h"

void InformationManager::_init(){
	// khởi tạo tìm vùng bắt đầu của mình và đối thủ	
	BWTA::readMap();
	BWTA::analyze();

	_nextGather = Position(10000, 10000);
	_scouterDied = false;

	_self = 0;
	_enemy = 4;

	for (auto & u : Broodwar->self()->getUnits()){
		if (u->exists()){			
			_self++;
		}
	}	

	for (BWTA::BaseLocation * startLocation : BWTA::getStartLocations())
	{
		TilePosition _tilePosition = startLocation->getTilePosition();		
		if (!Broodwar->isVisible(_tilePosition))
		{
			_baseEnemyLocation = startLocation;
		}
		else {
			_baseSelfLocation = startLocation;
		}
	}

	// update những thứ đã có
	update_have();
	// khởi tạo building order ở đây
	_buildOrder.update(_strategy, _have);
	// Chỉ có 4 con Micros
	_numOfMicros = 4;
	_maxOfMicros = 10;
}

void InformationManager::update_have(){	
	for (auto & u : Broodwar->self()->getUnits()){
		_have[u->getType()] = true;
	}
}

void InformationManager::update(){	
	
	// Cập nhật những thứ đã có
	update_have();
	// Cập nhật chiến thuật và suy ra buildorder 
	_strategy.update();
	_buildOrder.update(_strategy, _have);

	// Cập nhật số lượng thành phần enemy theo time
	_oldEnemy = _enemy;
	for (auto & u : Broodwar->enemy()->getUnits()) _enemy++;
	// Cập nhật quân mình theo time
	_oldSelf = _self;
	for (auto & u : Broodwar->self()->getUnits()) _self++;

	// cập nhật số micros và max Micro nữa.
	_numOfMicros = 0;
	for (auto & u : Broodwar->self()->getUnits()){
		if (!u->getType().isBuilding()){
			_numOfMicros++;
		}
	}
	_maxOfMicros = 0;
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType() == UnitTypes::Terran_Command_Center){
			_maxOfMicros += 10;
		}
		else if (u->getType() == UnitTypes::Terran_Supply_Depot){
			_maxOfMicros += 8;
		}
	}
}