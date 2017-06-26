#pragma once
#include <windows.h>
#include <BWTA.h>
#include <BWAPI.h>
#include "StrategyManager.h"
#include "BuildOrderManager.h"

using namespace BWAPI;

class InformationManager{
public:		
	int _numOfMicros;
	int _maxOfMicros;
	Position _nextGather;
	bool _scouterDied;

	map <UnitType, bool> _have;
	StrategyManager _strategy;
	BuildOrderManager _buildOrder;

	BWTA::BaseLocation *_baseEnemyLocation;
	BWTA::BaseLocation *_baseSelfLocation;		

	int _oldSelf;
	int _self;
	int _oldEnemy;
	int _enemy;
	void _init();
	void update();
	void update_have();
};