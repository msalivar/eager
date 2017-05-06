#include "SoundManager.h"
#include "Engine.h"

ALenum SoundMgr::error;
ALuint SoundMgr::backgroundBuffer;
ALuint SoundMgr::backgroundSource;
ALuint SoundMgr::idleBuffer;
ALuint SoundMgr::idleSource;
ALuint SoundMgr::moveBuffer;
ALuint SoundMgr::moveSource;
ALuint SoundMgr::shootBuffer;
ALuint SoundMgr::shootSource;

SoundMgr::SoundMgr(Engine *eng): Manager(eng)
{
	this->engine = eng;
}

SoundMgr::~SoundMgr()
{
	SoundMgr::closeAudio();
}

void SoundMgr::init()
{
	std::cout << "Sound Init" << std::endl;
	alutInit(0, NULL);
	alGetError();

	//Create Buffers
	std::cout << "Creating Buffers" << std::endl;
	SoundMgr::backgroundBuffer = alutCreateBufferFromFile("../assets/sounds/background.wav"); 
	if((SoundMgr::error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	//Generate Sources
	std::cout << "Generating sources" << std::endl;
	alGenSources(1, &SoundMgr::backgroundSource);
	if((SoundMgr::error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	//Link sources to buffers
	std::cout << "Linking sources to buffers" << std::endl;
	alSourcei(SoundMgr::backgroundSource, AL_BUFFER, SoundMgr::backgroundBuffer);
	if((SoundMgr::error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));
}

void SoundMgr::stop()
{

}

void SoundMgr::loadLevel()
{
	playBackgroundSound();
}

void SoundMgr::playBackgroundSound()
{
	std::cout << "Playing background sound" << std::endl;
	alSourcePlay(SoundMgr::backgroundSource);
	if((SoundMgr::error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play laser: %s\n",alutGetErrorString(error));
}

void SoundMgr::playIdleSound()
{

}

void SoundMgr::playMoveSound()
{

}

void SoundMgr::playShootSound()
{

}

void SoundMgr::closeAudio()
{
	alutSleep(1);
	alutExit();
}