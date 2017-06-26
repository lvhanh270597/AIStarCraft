#include "GameCommander.h"

GameCommander::GameCommander(){
	//Initialize Information
	_info._init();	
}

InformationManager & GameCommander::getInfo(){
	return _info;
}

void GameCommander::processing(InformationManager & info){
	_squads.doSomething(info);
}

void GameCommander::update(){
	_info.update();
	_squads.update(_info);	
}