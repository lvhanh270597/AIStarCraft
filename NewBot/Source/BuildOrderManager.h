#pragma once
#include "StrategyManager.h"
#include <map>
#include <vector>

class BuildOrderManager{
	bool _isAssigned;
	// squadBuild sẽ thay đổi biến này
	deque<UnitType> _buildings;	
	vector<UnitType> _buildZerg, _buildTerran, _buildProtoss;

public:	
	map<UnitType, deque<UnitType>> _need;
	BuildOrderManager();
	deque<UnitType> & getBuilding();
	void update(StrategyManager &, map <UnitType, bool> &);
};