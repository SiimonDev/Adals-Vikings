#pragma once
#include <string>

struct Dialog
{
	Dialog() :
		mDialog(""), mTimer(0), mDefault(false)
	{
	}

	Dialog(std::string lineOfDialog, float dialogLength) :
		mDialog(lineOfDialog), mTimer(dialogLength), mDefault(false)
	{
	}

	std::string mDialog;
	double mTimer;
	bool mDefault;
};

struct CombineDialog : public Dialog
{
	CombineDialog():
		Dialog()
	{
	}

	CombineDialog(std::string dialog, float timer, std::string resultID) : 
		Dialog(dialog, timer), mResultID(resultID)
	{
	}

	void operator=(Dialog& dialog)
	{
		mDefault = dialog.mDefault;
		mTimer = dialog.mTimer;
		mDialog = dialog.mDialog;
		mResultID = "";
	}

	std::string mResultID;
};