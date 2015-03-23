#pragma once
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <string>


namespace sf
{
	class VideoFile
	{
	public:
		enum Status
		{
			Playing,
			Stopped,
			Paused
		};

		VideoFile();
		VideoFile(std::string file, bool loop = false);
		//~VideoFile();

		bool openFromFile(std::string file, bool loop = false);
		void update(sf::Time frameTime);
		void render(sf::RenderWindow &window);
		
		void setPosition(const sf::Vector2f &position);
		void setPosition(const float x, const float y);
		void setSize(const sf::Vector2f &size);
		void setSize(const float x, const float y);

		void play();
		void pause();
		void stop();
		void restart();
		void close();

		sf::Vector2f getPosition();
		sf::Vector2f getSize();
		sf::Vector2i getRenderSize();
		Status getStatus();
		bool isLoaded();

	private:
		void flipIt(void* buffer);
		bool OpenAVI(LPCSTR szFile);
		void GrabAVIFrame(int frame);
		void CloseAVI();

		sf::Time mNext;
		sf::Time mMillisecondsPerFrame;
		
		Status mStatus;

		sf::Vector2f mPosition;
		sf::Vector2f mSize;

		int	mFrame = 0;
		long mLastframe;

		int	mWidth;
		int	mHeight;
		char* pdata;

		bool mLoop;
		bool mLoaded;
	};
}