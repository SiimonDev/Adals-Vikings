#include "ParallelLoader.h"
#include "..\Levels\LevelManager.h"
#include <iostream>

ParallelLoader::ParallelLoader()
: mFinished(false)
{
}

void ParallelLoader::execute(std::string task)
{
	mTask = task;
	mThread = ThreadPtr(new sf::Thread(&ParallelLoader::runTask, this));
	mFinished = false;
	mThread->launch();
}

bool ParallelLoader::isFinished()
{
	return mFinished;
}

void ParallelLoader::runTask()
{
	// Dummy task - stall 10 seconds
	if (mTask == "StartGame")
	{
		LVLMI.load();
	}
	else if (mTask == "LoadAct1")
	{
		LVLMI.unloadCurrentAct();
		LVLMI.loadAct1();
	}

	mFinished = true;
	mThread->terminate();
}
