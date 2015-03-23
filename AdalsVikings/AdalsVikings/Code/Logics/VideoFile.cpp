#include "VideoFile.h"
#include <iostream>
#include <vfw.h>
#include "WindowState.h"

using namespace sf;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "vfw32.lib" )

// Internal render resolution
//#define RENDER_WIDTH 1920
//#define RENDER_HEIGHT 1080

AVISTREAMINFO		psi;										// Pointer To A Structure Containing Stream Info
PAVISTREAM			pavi;										// Handle To An Open Stream
PGETFRAME			pgf;										// Pointer To A GetFrame Object
BITMAPINFOHEADER	bmih;										// Header Information For DrawDibDraw Decoding

HDRAWDIB hdd;													// Handle For Our Dib
HBITMAP hBitmap;												// Handle To A Device Dependant Bitmap
HDC hdc = CreateCompatibleDC(0);								// Creates A Compatible Device Context
unsigned char* data = 0;										// Pointer To Our Resized Image

GLuint textureID;

VideoFile::VideoFile() :
mFrame(0),
mWidth(0),
mHeight(0),
mPosition(0, 0),
mSize(0, 0),
mLoop(false),
mLoaded(false),
mStatus(Status::Stopped),
mNext(sf::seconds(0))
{
}
VideoFile::VideoFile(std::string file, bool loop) :
mFrame(0),
mWidth(0),
mHeight(0),
mPosition(0, 0),
mSize(0, 0),
mLoop(loop),
mLoaded(false),
mStatus(Status::Stopped),
mNext(sf::seconds(0))
{
	openFromFile(file, loop);
}

bool VideoFile::openFromFile(std::string file, bool loop)
{
	bool success = true;
	mLoop = loop;
	mStatus = Status::Stopped;

	hdd = DrawDibOpen();
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	if (!OpenAVI(file.c_str()))
		success = false;

	if (success)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		mLoaded = true;
	}

	return success;
}

void VideoFile::update(sf::Time frameTime)
{
	if (mStatus == Status::Playing && mLoaded)
	{
		mNext += frameTime;
		mFrame = int(mNext.asMilliseconds() / mMillisecondsPerFrame.asMilliseconds());

		if (mFrame >= mLastframe)
		{
			if (mLoop)
			{
				mFrame = 0;
				mNext = sf::seconds(0);
			}
			else
			{
				mFrame = mLastframe - 1;
				mStatus = Status::Paused;
			}
		}
	}
}
void VideoFile::render(sf::RenderWindow &window)
{
	if (mStatus != Status::Stopped && mLoaded)
	{
		sf::Vector2u physicalSize = window.getSize();
		sf::Vector2f virtualSize = window.getView().getSize();

		window.resetGLStates();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		gluOrtho2D(0.0f, virtualSize.x, 0.0f, virtualSize.y);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		GrabAVIFrame(mFrame);
		glLoadIdentity();
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(mPosition.x, mPosition.y, 0);
		glTexCoord2f(0, 1); glVertex3f(mPosition.x, mPosition.y + mSize.y, 0);
		glTexCoord2f(1, 1); glVertex3f(mPosition.x + mSize.x, mPosition.y + mSize.y, 0);
		glTexCoord2f(1, 0); glVertex3f(mPosition.x + mSize.x, mPosition.y, 0);
		glEnd();

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		window.resetGLStates();
	}
}

void VideoFile::setPosition(const sf::Vector2f &position)
{
	mPosition = position;
}
void VideoFile::setPosition(const float x, const float y)
{
	mPosition = sf::Vector2f(x, y);
}
void VideoFile::setSize(const sf::Vector2f &size)
{
	mSize = size;
}
void VideoFile::setSize(const float x, const float y)
{
	mSize = sf::Vector2f(x, y);
}

void VideoFile::play()
{
	mStatus = Status::Playing;
}
void VideoFile::pause()
{
	mStatus = Status::Paused;
}
void VideoFile::stop()
{
	mStatus = Status::Stopped;
}
void VideoFile::restart()
{
	mFrame = 0;
	mNext = sf::seconds(0);
}
void VideoFile::close()
{
	mLoaded = false;
	CloseAVI();
	glDeleteTextures(1, &textureID);
}

sf::Vector2f VideoFile::getPosition()
{
	return mPosition;
}
sf::Vector2f VideoFile::getSize()
{
	return mSize;
}
sf::Vector2i VideoFile::getRenderSize()
{
	return sf::Vector2i(mWidth, mHeight);
}
VideoFile::Status VideoFile::getStatus()
{
	return mStatus;
}
bool VideoFile::isLoaded()
{
	return mLoaded;
}

void VideoFile::flipIt(void* buffer)							// Flips The Red And Blue Bytes (256x256)
{
	const int pixels = mWidth * mHeight;
	void* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, pixels											// Counter Set To Dimensions Of Our Memory Block
			mov ebx, b											// Points ebx To Our Data (b)
		label :													// Label Used For Looping
		mov al, [ebx + 0]										// Loads Value At ebx Into al
			mov ah, [ebx + 2]									// Loads Value At ebx+2 Into ah
			mov[ebx + 2], al									// Stores Value In al At ebx+2
			mov[ebx + 0], ah									// Stores Value In ah At ebx

			add ebx, 3											// Moves Through The Data By 3 Bytes
			dec ecx												// Decreases Our Loop Counter
			jnz label											// If Not Zero Jump Back To Label
	}
}
bool VideoFile::OpenAVI(LPCSTR szFile)
{
	bool success = true;
	AVIFileInit();													// Opens The AVIFile Library

	if (AVIStreamOpenFromFile(&pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) != 0)
	{
		MessageBox(HWND_DESKTOP, "Failed To Open The AVI Stream.\nMake sure you are not missing any video files", "Error", MB_OK | MB_ICONEXCLAMATION);
		success = false;
	}

	if (success)
	{
		AVIStreamInfo(pavi, &psi, sizeof(psi));							// Reads Information About The Stream Into psi
		mWidth = psi.rcFrame.right - psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
		mHeight = psi.rcFrame.bottom - psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top
		mSize = sf::Vector2f(mWidth, mHeight);

		mLastframe = AVIStreamLength(pavi);								// The Last Frame Of The Stream

		mMillisecondsPerFrame = sf::milliseconds(AVIStreamSampleToTime(pavi, mLastframe) / mLastframe);

		bmih.biSize = sizeof(BITMAPINFOHEADER);							// Size Of The BitmapInfoHeader
		bmih.biPlanes = 1;												// Bitplanes	
		bmih.biBitCount = 24;											// Bits Format We Want (24 Bit, 3 Bytes)
		bmih.biWidth = mWidth;											// Width We Want
		bmih.biHeight = mHeight;										// Height We Want
		bmih.biCompression = BI_RGB;									// Requested Mode = RGB

		hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
		SelectObject(hdc, hBitmap);										// Select hBitmap Into Our Device Context (hdc)

		pgf = AVIStreamGetFrameOpen(pavi, NULL);						// Create The PGETFRAME	Using Our Request Mode
		if (pgf == NULL)
		{
			MessageBox(HWND_DESKTOP, "Failed To Open The AVI Frame\nTry reinstalling x264vfw", "Error", MB_OK | MB_ICONEXCLAMATION);
			success = false;
		}

		if (success)
			std::cout << "Loaded AVI File: Width : " << mWidth << " Height : " << mHeight << " Frames : " << mLastframe << std::endl;
		else
			std::cout << "Failde to load AVI file, missing x264vfw codec" << std::endl;
	}
	else
		std::cout << "Failde to load AVI file" << std::endl;
	
	return success;
}
void VideoFile::GrabAVIFrame(int frame)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);

	DrawDibDraw(hdd, hdc, 0, 0, mWidth, mHeight, lpbi, pdata, 0, 0, mWidth, mHeight, 0);
	
	flipIt(data);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
}
void VideoFile::CloseAVI()
{
	DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
	DrawDibClose(hdd);											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
	AVIStreamRelease(pavi);										// Release The Stream
	AVIFileExit();												// Release The File
}