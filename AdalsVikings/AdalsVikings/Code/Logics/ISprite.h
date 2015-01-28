#pragma once
#include <SFML\Graphics.hpp>

namespace mv
{
	class ISprite
	{
	public:
		sf::Sprite &getSprite() { return mSprite; }
		int getIndex() { return mIndex; }

		ISprite(){
			mIndex = 0;
		}
		ISprite(sf::Texture &tex, int index = 0){
			mSprite.setTexture(tex);
			mIndex = index;
		}

		void setIndex(int index){
			mIndex = index;
		}

		ISprite& operator=(const ISprite &isprite){
			mSprite = isprite.mSprite;
			mIndex = isprite.mIndex;
			return *this;
		}

	private:
		sf::Sprite mSprite;
		int mIndex;
	};
}