#include "NewBot.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void NewBot::onStart()
{	
	
	Broodwar->sendText("Hey!!! My bot!");
	
	Broodwar->enableFlag(Flag::UserInput);

	Broodwar->setCommandOptimizationLevel(2);
}

void NewBot::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		// Log your win here!
	}
}

void NewBot::onFrame()
{
	_gameCommander.processing(_gameCommander.getInfo());	
	if (Broodwar->getFrameCount() % 100) _gameCommander.update();
}

void NewBot::onSendText(std::string text)
{
	Broodwar->sendText("%s", text.c_str());
}

void NewBot::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void NewBot::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void NewBot::onNukeDetect(BWAPI::Position target)
{

	// Check if the target is a valid position
	if (target)
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}

	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void NewBot::onUnitDiscover(BWAPI::Unit unit)
{
}

void NewBot::onUnitEvade(BWAPI::Unit unit)
{
}

void NewBot::onUnitShow(BWAPI::Unit unit)
{
}

void NewBot::onUnitHide(BWAPI::Unit unit)
{
}

void NewBot::onUnitCreate(BWAPI::Unit unit)
{
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void NewBot::onUnitDestroy(BWAPI::Unit unit)
{
}

void NewBot::onUnitMorph(BWAPI::Unit unit)
{
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void NewBot::onUnitRenegade(BWAPI::Unit unit)
{
}

void NewBot::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void NewBot::onUnitComplete(BWAPI::Unit unit)
{
}
