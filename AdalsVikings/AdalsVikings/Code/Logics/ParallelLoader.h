#pragma once
#include <SFML/System/Thread.hpp>
#include <memory>
#include <string>

typedef std::unique_ptr<sf::Thread> ThreadPtr;

class ParallelLoader
{
public:

	ParallelLoader();

	void execute(std::string task);
	bool isFinished();

private:

	void runTask();

	ThreadPtr mThread;
	std::string mTask;
	bool mFinished, mStarted;
};

