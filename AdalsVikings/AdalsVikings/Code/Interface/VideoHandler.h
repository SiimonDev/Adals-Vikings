#include "..\Logics\VideoFile.h"

#define VideoHandlerI VideoHandler::getInstance()

class VideoHandler
{
public:
	static VideoHandler &getInstance()
	{
		static VideoHandler instance;
		return instance;
	}

	sf::VideoFile &getSplashScreen()
	{
		mSplashScreen.openFromFile("assets/video/SplashScreen_x264_720p.avi", "assets/video/SplashScreen_sound.ogg");
		mSplashScreen.setSize(1280, 720);
		mSplashScreen.setPosition((1920 / 2) - mSplashScreen.getSize().x / 2, (1080 / 2) - mSplashScreen.getSize().y / 2);
		return mSplashScreen;
	}

	sf::VideoFile &getCredits()
	{
		mEndCredits.openFromFile("assets/video/ending_credits_x264_720p.avi", "assets/video/ending_credits_sound.ogg");
		mEndCredits.setSize(1920, 1080);
		return mEndCredits;
	}

	bool endCreditsPlaying()
	{
		return mEndCredits.getStatus() == sf::VideoFile::Playing;
	}

private:
	VideoHandler(){}
	
	sf::VideoFile mSplashScreen;
	sf::VideoFile mEndCredits;
};