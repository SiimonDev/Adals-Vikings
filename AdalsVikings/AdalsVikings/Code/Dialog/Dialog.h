#pragma once
#include <string>

struct Dialog
{
	Dialog() :
		mDialog(""), mTimer(0)
	{
	}

	Dialog(std::string lineOfDialog, float dialogLength) :
	 	mDialog(lineOfDialog), mTimer(dialogLength)
	{
	}

	std::string mDialog;
	double mTimer;
};

struct CombineDialog
{
	CombineDialog() :
		mDialog(""), mTimer(0), mResultID("")
	{
	}

	CombineDialog(std::string dialog, float timer, std::string resultID) :
		mDialog(dialog), mTimer(timer), mResultID(resultID)
	{
	}

	std::string mResultID;
	std::string mDialog;
	double mTimer;
};