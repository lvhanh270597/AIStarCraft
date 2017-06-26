#include "SquadAttack.h"

Unit SquadAttack::getEnemyNearest(Unit u){
	Unit _goal = nullptr;
	double minDistance = 1000000;
	for (auto & e : Broodwar->enemy()->getUnits())
		if (e->exists() && distance(u, e) < minDistance && e->getType() != UnitTypes::Zerg_Overlord){
			minDistance = distance(u, e);
			_goal = e;
		}
	return _goal;
}

bool SquadAttack::enoughPower(Unit & unitCenter){
	// Nếu unit này đã chết thì khỏi xét	
	if (!unitCenter->exists()) return false;
	// Tính không gian xung quanh nó maxPixcel
	double maxDistance = 800;
	double hs = 0;
	for (auto & u : _units){
		if (u->exists() && distance(u, unitCenter) <= maxDistance){			
			BWAPI::WeaponType wu = u->getType().groundWeapon();
			int _below = wu.damageCooldown() == 0 ? 1 : wu.damageCooldown();						
			hs += double(u->getHitPoints() * wu.damageAmount()) / _below;			
		}
	}

	double he = 0;
	for (auto & e : Broodwar->enemy()->getUnits()) {
		if (e->exists() && distance(e, unitCenter) <= maxDistance) {
			BWAPI::WeaponType we = e->getType().groundWeapon();
			int _below = we.damageCooldown() == 0 ? 1 : we.damageCooldown();
			he += double(e->getHitPoints() * we.damageAmount()) / _below;
		}
	}	
	
	return hs > he;
}

double SquadAttack::distance(Unit u, Unit v){
	int x0 = u->getPosition().x;
	int y0 = u->getPosition().y;
	int x1 = v->getPosition().x;
	int y1 = v->getPosition().y;
	return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1) *(y0 - y1));
}

WeaponType getWeapon(Unit u){
	if (u->isFlying() || u->getType().isFlyer()) return u->getType().airWeapon();
	else return u->getType().groundWeapon();
}

double getHP(Unit u){
	return u->getHitPoints() + u->getShields();
}

double SquadAttack::evaluate(double hp, double damageAmount, double damageCooldown){
	return damageCooldown == 0 ? hp * damageAmount : hp * damageAmount / damageCooldown;
}

void SquadAttack::findConnectedMyArmy(Unit unitCenter, double maxDistance, double & myPower){
	check[unitCenter] = true;
	checkMy[unitCenter] = true;
	myPower += evaluate(getHP(unitCenter), getWeapon(unitCenter).damageAmount(), getWeapon(unitCenter).damageCooldown());
	for (auto & u : _units){
		if (distance(unitCenter, u) <= maxDistance && !checkMy[u]){
			findConnectedMyArmy(u, maxDistance, myPower);
		}
	}
}

bool canAttack(Unit u, Unit v){
	return (distance(u, v) <= getWeapon(u).maxRange());
}

void SquadAttack::findConnectedEnemyArmy(Unit unitCenter, double maxDistance, double & enemyPower){
	checkEnemy[unitCenter] = true;
	for (auto & u : _units){
		if (checkMy[u] && canAttack(unitCenter, u)){
			enemyPower += evaluate(getHP(unitCenter), getWeapon(unitCenter).damageAmount(), getWeapon(unitCenter).damageCooldown());
			break;
		}
	}	
	for (auto & e : Broodwar->enemy()->getUnits()){
		if (distance(unitCenter, e) <= maxDistance && !checkEnemy[e]){
			findConnectedEnemyArmy(e, maxDistance, enemyPower);
		}
	}
}

void SquadAttack::doSomething(InformationManager & info){
	// vị trí nhà:
	Position rs = info._baseSelfLocation->getPosition();
	Position re = info._baseEnemyLocation->getPosition();
	double maxDistance = 50;

	check.clear();
	for (auto & u : _units) {		
		if (u->exists() && !check[u]){
			double myPower = 0;				
			checkMy.clear();
			findConnectedMyArmy(u, maxDistance, myPower);

			Unit e = getEnemyNearest(u);
			if (e){
				double enemyPower = 0;				
				checkEnemy.clear();
				findConnectedEnemyArmy(e, maxDistance, enemyPower);

				if (myPower > enemyPower || distance(e, u) >= 500) {
					Broodwar->sendText("attack!");
					for (auto & U : _units)
						if (checkMy[U]) {
							if (U->isIdle() || !isAttacking[U]) {
								U->attack(e->getPosition());
								isAttacking[U] = true;
							}
						}
				}
				else {
					Broodwar->sendText("retreat!");
					for (auto & U : _units)
						if (checkMy[U]) {						
							if (isAttacking[U]){
								U->move(rs);
								isAttacking[U] = false;
							}
						}					
				}
			}
			else{
				for (auto & U : _units)
					if (checkMy[U]){
						if (U->isIdle() || !isAttacking[U]) {
							U->attack(re);
							isAttacking[U] = true;
						}
					}				
			}			
		}
	}
}

bool SquadAttack::_needToTogether(int i, InformationManager & info){	
}

void SquadAttack::update(InformationManager & info){	
}