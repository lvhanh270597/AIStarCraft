#include "SquadScout.h"

int Distance(Position a, Position b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}

char * SquadScout::convert(int x){	
	if (x == 0) {
		s[0] = 48;
		s[1] = '\0';
		return s;
	}
	int n = 0;
	while (x > 0){
		s[n] = 48 + x % 10;
		x /= 10;
		n++;
	}
	for (int i = 0; i < n / 2; i++) swap(s[i], s[n - i - 1]);
	s[n] = '\0';
	return s;
}

void SquadScout::doSomething(InformationManager & info){	

	Position _center = info._baseEnemyLocation->getPosition();

	if (Broodwar->getFrameCount() == 0) {					
		cnt = 0;
		_lastLostHP = 10000;
		_assignNextGather = false;
		_go.push_back(_center);
		_go.push_back(Position(_center.x - 200, _center.y - 200));
		_go.push_back(Position(_center.x - 200, _center.y + 200));
		_go.push_back(Position(_center.x + 200, _center.y + 200));
		_go.push_back(Position(_center.x + 200, _center.y - 200));

		for (auto & u : _units)
			_maxHitPoint = u->getHitPoints();
	}
	int hp = 0;
	int distance = 0;
	for (auto & u : _units){
		hp = u->getHitPoints();
		distance = u->getDistance(info._baseEnemyLocation->getPosition());		
	}
	if (!info._scouterDied && (hp == _maxHitPoint && distance < 500)){
		_lastLostHP = Broodwar->getFrameCount();
		cnt = 1;
		for (auto & u : _units)
			if (u->isIdle()) u->attack(_center);
	}
	else{		
		for (auto & u : _units) {
			if (u->canGather(u->getClosestUnit(Filter::IsMineralField)) && 
				u->getDistance(info._baseSelfLocation->getPosition()) - u->getDistance(u->getClosestUnit(Filter::IsMineralField)) > 500 
				&& Distance(info._nextGather, info._baseSelfLocation->getPosition()) > 
				Distance(info._baseSelfLocation->getPosition(), u->getClosestUnit(Filter::IsMineralField)->getPosition())){

				info._nextGather = u->getClosestUnit(Filter::IsMineralField)->getPosition();
				Broodwar->sendText("found a new Mineral");
			}

			if (info._scouterDied && !_assignNextGather){				
				static int cf = 0;
				Broodwar->sendText("assigned _go again!");
				_assignNextGather = true;
				_go.clear();
				cnt = 1;
				_center = info._baseSelfLocation->getPosition();
				_go.push_back(_center);					
				BWTA::Region *last = info._baseSelfLocation->getRegion();
				for (auto & region : BWTA::getRegions()){					
					if (Distance(region->getCenter(), info._baseEnemyLocation->getPosition()) < 500) continue;					
					if (last->isReachable(region)) _go.push_back(region->getCenter());
					last = region;
				}
				Broodwar->sendText("kiem duoc ");
				Broodwar->sendText(convert((int)_go.size()));
			}						
			u->move(_go[cnt]);
			if (u->getDistance(_go[cnt]) < 50) cnt++;				
			if (cnt == _go.size()) cnt = 1;
		}
	}
}