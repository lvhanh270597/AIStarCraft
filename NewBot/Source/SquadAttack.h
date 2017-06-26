#include <BWAPI.h>
#include "Squad.h"
#include "InformationManager.h"
#include <vector>
#include <map>

using namespace std;
using namespace BWAPI;

class SquadAttack : public Squad{
	map <Unit, bool> isAttacking;
	map <Unit, bool> check;
	map <Unit, bool> checkEnemy;
	map <Unit, bool> checkMy;
public:
	bool enoughPower(Unit &);
	void doSomething(InformationManager &);
	void update(InformationManager &);
	bool _needToTogether(int, InformationManager &);
	double distance(Unit, Unit);
	void findConnectedMyArmy(Unit, double, double &);
	void findConnectedEnemyArmy(Unit, double, double &);
	double evaluate(double, double, double);
	Unit getEnemyNearest(Unit);
};