#pragma once
#include "Squad.h"
#include "InformationManager.h"
#include <BWTA.h>

class SquadScout : public Squad{
	char s[8];
	int _maxHitPoint;
	int _lastLostHP;
	std::vector <Position> _go;
	bool _assignNextGather;
public:
	int cnt;
	char *convert(int);
	void doSomething(InformationManager &);
};