#pragma once

#include <deque>
#include <BWAPI.h>

using namespace BWAPI;
using namespace std;

class StrategyManager{
	// squadBuild cũng sẽ thay đổi biến này
	std::string strategyName;
	deque<UnitType> _chars;
public:
	StrategyManager();
	deque<UnitType> & getBuildCharacters();
	std::string & getStrategyName();
	void update();
};