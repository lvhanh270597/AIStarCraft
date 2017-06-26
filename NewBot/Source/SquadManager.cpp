#include <BWAPI.h>
#include "SquadManager.h"

SquadManager::SquadManager(){
		
	_squadScout.setType(SquadT::SquadType::Scout);
	_squadProduce.setType(SquadT::SquadType::Produce);
	_squadGather.setType(SquadT::SquadType::Gather);
	_squadBuild.setType(SquadT::SquadType::Build);
	_squadAttack.setType(SquadT::SquadType::Attack);

	int count = 0;
	for (auto & u : Broodwar->self()->getUnits()){
		Unit & v = (Unit)u;
		if (u->getType().isWorker()){
			if (count == 0){
				count++;
				_squadScout.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Scout;
			}
			else if (count == 1){
				count++;
				_squadBuild.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Build;
			}
			else if (count == 2){
				count++;
				_supplyMan.getUnit() = v;
				isAssigned[v] = SquadT::SquadType::Build;
			}
			else{
				_squadGather.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Gather;
			}
		}			
		if (u->getType() == UnitTypes::Terran_Command_Center){
			_squadProduce.addUnit(v);
			isAssigned[v] = SquadT::SquadType::Produce;
		}
	}
}
void SquadManager::update(InformationManager & info){

	_squadGather.update();
	_squadScout.update();
	_squadProduce.update();
	_squadBuild.update();
	_squadAttack.update(info);

	balance(info);
}

void SquadManager::balance(InformationManager & info){	
	// Nếu nó là worker vừa mới tạo ra thì nó sẽ được thêm vào đội hình Gather
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isWorker()){
			Unit & v = (Unit)u;
			if (!isAssigned[v]){
				_squadGather.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Gather;
			}
		}
	}
	// Nếu con Supply depot đã chết thì kiếm đại 1 con trong đội hình Gather
	if (!_supplyMan.getUnit()->exists()){
		Unitset units;
		int count = 0;					
		for (auto & u : _squadGather.getUnits()){
			Unit & v = (Unit)u;
			if (count > 0){
				units.insert(v);
				isAssigned[v] = SquadT::SquadType::Gather;
			}
			else {					
				isAssigned[v] = SquadT::SquadType::Build;
				_supplyMan.getUnit() = v;
				count++;
			}
		}
		_squadGather.getUnits() = units;
	}
	// Mọi cái building tạo ra đều thuộc Produce trừ Supply Depot 
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType().isBuilding() && u->getType() != UnitTypes::Terran_Supply_Depot){
			Unit & v = (Unit)u;
			if (!isAssigned[v]){
				_squadProduce.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Produce;
			}
		}
	} 
	//Nếu con scout đã chết, thì lấy 1 con khác bên đội hình gather để thay thế	
	Unitset units;
	int count = 0;
	if (_squadScout.getCount() == 0){		
		//		
		info._scouterDied = true;
		for (auto & u : _squadGather.getUnits()){
			Unit & v = (Unit)u;
			if (count > 0){
				units.insert(v);
				isAssigned[v] = SquadT::SquadType::Gather;
			}
			else {				
				isAssigned[v] = SquadT::SquadType::Scout;
				_squadScout.addUnit(v);
				_squadScout.cnt = 1;
				count++;
			}			
		}
		_squadGather.getUnits() = units;
	}	

	// Mọi con Marine, Medic sinh ra đều thuộc đội hình tấn công.
	for (auto & u : Broodwar->self()->getUnits()){
		if (u->getType() == UnitTypes::Terran_Marine || u->getType() == UnitTypes::Terran_Medic){
			Unit & v = (Unit)u;
			if (!isAssigned[v]){
				_squadAttack.addUnit(v);
				isAssigned[v] = SquadT::SquadType::Attack;
			}
		}
	}
}

Squad & SquadManager::getSquad(SquadT::SquadType id){
	if (id == SquadT::SquadType::Scout) return _squadScout;
	//if (id == SquadType::Protected) return _squadProtected;
	//if (id == SquadType::Attack) return _squadAttack;
	//if (id == SquadType::Build) return _squadBuild;
	if (id == SquadT::SquadType::Produce) return _squadProduce;
	if (id == SquadT::SquadType::Gather) return _squadGather;
}
void SquadManager::doSomething(InformationManager & info){	
	_squadGather.doSomething(info);
	_squadProduce.doSomething(info);
	_squadScout.doSomething(info);
	_squadBuild.doSomething(info);
	_supplyMan.doSomething(info);
	_squadAttack.doSomething(info);
}
// hàm để cân bằng lại squad
