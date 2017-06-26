#include "StrategyManager.h"

StrategyManager::StrategyManager(){
	UnitType arr[9] = { UnitTypes::Terran_Marine, UnitTypes::Terran_Machine_Shop };
	for (int i = 0; i < 2; i++) _chars.push_back(arr[i]);
}

deque<UnitType> & StrategyManager::getBuildCharacters(){
	return _chars;
}

void StrategyManager::update(){	

}

std::string & StrategyManager::getStrategyName(){
	return strategyName;
}