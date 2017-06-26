#include "Squad.h"

using namespace BWAPI;

Squad::Squad(){
	_type = SquadT::SquadType::None;
}

void Squad::addUnit(Unit & u){
	if (u->exists()){
		_units.insert(u);
	}
}

void Squad::update(){
	Unitset temp;
	for (auto &u : _units){		
		if (u->exists()) temp.insert(u);
	}
	_units = temp;
}

void Squad::setType(SquadT::SquadType type)
{
	_type = type;
}

SquadT::SquadType Squad::getType()
{
	return _type;
}

Unitset & Squad::getUnits()
{ 
	return _units; 
}

void Squad::setUnits(Unitset &units)
{
	_units.clear();
	_units = units;
}

int Squad::getCount()
{
	int count = 0;
	for (auto & u : _units)
		if (u->exists()) count++;
	return count;
}