#include "VideoFile.h"
#include <iostream>

using namespace sf;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "vfw32.lib" )

// Internal render resolution
#define RENDER_WIDTH 1920
#define RENDER_HEIGHT 1080

AVISTREAMINFO		psi;										// Pointer To A Structure Containing Stream Info
PAVISTREAM			pavi;										// Handle To An Open Stream
PGETFRAME			pgf;										// Pointer To A GetFrame Object
BITMAPINFOHEADER	bmih;										// Header Information For DrawDibDraw Decoding

HDRAWDIB hdd;													// Handle For Our Dib
HBITMAP hBitmap;												// Handle To A Device Dependant Bitmap
HDC hdc = CreateCompatibleDC(0);								// Creates A Compatible Device Context
unsigned char* data = 0;										// Pointer To Our Resized Image

VideoFile::VideoFile():
mFrame(0),
mWidth(0),
mHeight(0),
mPosition(0, 0),
mSize(0, 0),
mLoop(false),
mStatus(Status::Stopped)
{
}
VideoFile::VideoFile(std::string file, bool loop) :
mFrame(0),
mWidth(0),
mHeight(0),
mPosition(0, 0),
mSize(0, 0),
mLoop(loop),
mStatus(Status::Stopped)
{
	openFromFile(file, loop);
}

bool VideoFile::openFromFile(std::string file, bool loop)
{
	mLoop = loop;
	mStatus = Status::Stopped;

	hdd = DrawDibOpen();
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	//glClearDepth(1.0f);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	OpenAVI(file.c_str());

	// Create The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RENDER_WIDTH, RENDER_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return true;
}

void VideoFile::update(sf::Time frameTime)
{
	if (mStatus == Status::Playing)
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
	if (mStatus != Status::Stopped)
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
	CloseAVI();
}

VideoFile::Status VideoFile::getStatus()
{
	return mStatus;
}

void VideoFile::flipIt(void* buffer)							// Flips The Red And Blue Bytes (256x256)
{
	void* b = buffer;											// Pointer To The Buffer
	__asm														// Assembler Code To Follow
	{
		mov ecx, RENDER_WIDTH * RENDER_HEIGHT										// Counter Set To Dimensions Of Our Memory Block
			mov ebx, b												// Points ebx To Our Data (b)
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
void VideoFile::OpenAVI(LPCSTR szFile)
{
	AVIFileInit();													// Opens The AVIFile Library

	if (AVIStreamOpenFromFile(&pavi, szFile, streamtypeVIDEO, 0, OF_READ, NULL) != 0)
		MessageBox(HWND_DESKTOP, "Failed To Open The AVI Stream", "Error", MB_OK | MB_ICONEXCLAMATION);

	AVIStreamInfo(pavi, &psi, sizeof(psi));							// Reads Information About The Stream Into psi
	mWidth = psi.rcFrame.right - psi.rcFrame.left;					// Width Is Right Side Of Frame Minus Left
	mHeight = psi.rcFrame.bottom - psi.rcFrame.top;					// Height Is Bottom Of Frame Minus Top
	mSize = sf::Vector2f(mWidth, mHeight);

	mLastframe = AVIStreamLength(pavi);								// The Last Frame Of The Stream

	mMillisecondsPerFrame = sf::milliseconds(AVIStreamSampleToTime(pavi, mLastframe) / mLastframe);

	bmih.biSize = sizeof(BITMAPINFOHEADER);							// Size Of The BitmapInfoHeader
	bmih.biPlanes = 1;												// Bitplanes	
	bmih.biBitCount = 24;											// Bits Format We Want (24 Bit, 3 Bytes)
	bmih.biWidth = RENDER_WIDTH;									// Width We Want
	bmih.biHeight = RENDER_HEIGHT;									// Height We Want
	bmih.biCompression = BI_RGB;									// Requested Mode = RGB

	hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)(&bmih), DIB_RGB_COLORS, (void**)(&data), NULL, NULL);
	SelectObject(hdc, hBitmap);										// Select hBitmap Into Our Device Context (hdc)

	pgf = AVIStreamGetFrameOpen(pavi, NULL);						// Create The PGETFRAME	Using Our Request Mode
	if (pgf == NULL)
		MessageBox(HWND_DESKTOP, "Failed To Open The AVI Frame", "Error", MB_OK | MB_ICONEXCLAMATION);

	std::cout << "Loaded AVI File: Width : " << mWidth << " Height : " << mHeight << " Frames : " << mLastframe << std::endl;
}
void VideoFile::GrabAVIFrame(int frame)
{
	LPBITMAPINFOHEADER lpbi;
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);

	DrawDibDraw(hdd, hdc, 0, 0, RENDER_WIDTH, RENDER_HEIGHT, lpbi, pdata, 0, 0, mWidth, mHeight, 0);
	
	flipIt(data);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, RENDER_WIDTH, RENDER_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);
}
void VideoFile::CloseAVI()
{
	DeleteObject(hBitmap);										// Delete The Device Dependant Bitmap Object
	DrawDibClose(hdd);											// Closes The DrawDib Device Context
	AVIStreamGetFrameClose(pgf);								// Deallocates The GetFrame Resources
	AVIStreamRelease(pavi);										// Release The Stream
	AVIFileExit();												// Release The File
}