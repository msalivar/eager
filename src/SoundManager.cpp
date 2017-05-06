#include "SoundManager.h"
#include "Engine.h"

ALenum SoundMgr::error;
ALuint SoundMgr::menuBuffer;
ALuint SoundMgr::menuSource;
ALuint SoundMgr::musicBuffer1;
ALuint SoundMgr::musicSource1;
ALuint SoundMgr::musicBuffer2;
ALuint SoundMgr::musicSource2;
ALuint SoundMgr::musicBuffer3;
ALuint SoundMgr::musicSource3;
ALuint SoundMgr::idleBuffer;
ALuint SoundMgr::idleBuffer2;
ALuint SoundMgr::idleSource;
ALuint SoundMgr::idleSource2;
ALuint SoundMgr::moveBuffer;
ALuint SoundMgr::moveBuffer2;
ALuint SoundMgr::moveSource;
ALuint SoundMgr::moveSource2;
ALuint SoundMgr::shootBuffer;
ALuint SoundMgr::shootBuffer2;
ALuint SoundMgr::shootSource;
ALuint SoundMgr::shootSource2;

SoundMgr::SoundMgr(Engine *eng): Manager(eng)
{
	this->engine = eng;
}

SoundMgr::~SoundMgr()
{
}

void SoundMgr::init()
{
	std::cout << "Sound Init" << std::endl;
	alutInit(0, NULL);
	alGetError();

	//Create Buffers
	std::cout << "Creating Buffers" << std::endl;
	menuBuffer = alutCreateBufferFromFile("../assets/sounds/menuMusic.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	musicBuffer1 = alutCreateBufferFromFile("../assets/sounds/battleMusic1.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	musicBuffer2 = alutCreateBufferFromFile("../assets/sounds/battleMusic2.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	musicBuffer3 = alutCreateBufferFromFile("../assets/sounds/battleMusic3.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	idleBuffer = alutCreateBufferFromFile("../assets/sounds/tankIdle.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	idleBuffer2 = alutCreateBufferFromFile("../assets/sounds/tankIdle.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	moveBuffer = alutCreateBufferFromFile("../assets/sounds/tankMoving.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	moveBuffer2 = alutCreateBufferFromFile("../assets/sounds/tankMoving.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	shootBuffer = alutCreateBufferFromFile("../assets/sounds/tankShoot.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	shootBuffer2 = alutCreateBufferFromFile("../assets/sounds/tankShoot.wav"); 
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	//Generate Sources
	std::cout << "Generating sources" << std::endl;
	alGenSources(1, &menuSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &musicSource1);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &musicSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &musicSource3);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &idleSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &idleSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &moveSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &moveSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &shootSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alGenSources(1, &shootSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	//Link sources to buffers
	std::cout << "Linking sources to buffers" << std::endl;
	alSourcei(menuSource, AL_BUFFER, menuBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(musicSource1, AL_BUFFER, musicBuffer1);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(musicSource2, AL_BUFFER, musicBuffer2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(musicSource3, AL_BUFFER, musicBuffer3);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(idleSource, AL_BUFFER, idleBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(idleSource2, AL_BUFFER, idleBuffer2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(moveSource, AL_BUFFER, moveBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(moveSource2, AL_BUFFER, moveBuffer2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(shootSource, AL_BUFFER, shootBuffer);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	alSourcei(shootSource2, AL_BUFFER, shootBuffer2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error: %s\n",alutGetErrorString(error));

	// Set source attributes
	alSourcef(menuSource, AL_LOOPING, AL_TRUE);
	alSourcef(idleSource, AL_LOOPING, AL_TRUE);
	alSourcef(idleSource2, AL_LOOPING, AL_TRUE);
	alSourcef(moveSource, AL_LOOPING, AL_TRUE);
	alSourcef(moveSource2, AL_LOOPING, AL_TRUE);
	// Volume
	alSourcef(menuSource, AL_GAIN, 1.8f);
	alSourcef(musicSource1, AL_GAIN, 1.8f);
	alSourcef(musicSource2, AL_GAIN, 1.8f);
	alSourcef(musicSource3, AL_GAIN, 1.8f);
	alSourcef(idleSource, AL_GAIN, 0.7f);
	alSourcef(idleSource2, AL_GAIN, 0.7f);
	alSourcef(moveSource, AL_GAIN, 0.6f);
	alSourcef(moveSource2, AL_GAIN, 0.6f);
	alSourcef(shootSource, AL_GAIN, 0.9f);
	alSourcef(shootSource2, AL_GAIN, 0.9f);
}

void SoundMgr::stop()
{
	alutSleep(1);
	alutExit();
}

void SoundMgr::loadLevel()
{
}

void SoundMgr::playMusic(int id)
{
	switch (id)
	{
		case 0:
			alSourcePlay(menuSource);
			break;
		case 1:
			alSourcePlay(musicSource1);
			break;
		case 2:
			alSourcePlay(musicSource2);
			break;
		case 3:
			alSourcePlay(musicSource3);
			break;
		default:
			fprintf(stderr, "Bad music ID");
			break;
	}
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play music: %s\n",alutGetErrorString(error));
}

void SoundMgr::stopMusic(int id)
{
	switch (id)
	{
		case 0:
			alSourceStop(menuSource);
			break;
		case 1:
			alSourceStop(musicSource1);
			break;
		case 2:
			alSourceStop(musicSource2);
			break;
		case 3:
			alSourceStop(musicSource3);
			break;
		default:
			fprintf(stderr, "Bad music ID");
			break;
	}
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - stop music: %s\n",alutGetErrorString(error));
}

void SoundMgr::playIdleSound()
{
	alSourcePlay(idleSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play idle: %s\n",alutGetErrorString(error));
}

void SoundMgr::playIdleSoundPTwo()
{
	alSourcePlay(idleSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play idle: %s\n",alutGetErrorString(error));
}

void SoundMgr::stopIdleSound()
{
	alSourceStop(idleSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - stop idle: %s\n",alutGetErrorString(error));
}

void SoundMgr::stopIdleSoundPTwo()
{
	alSourceStop(idleSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - stop idle: %s\n",alutGetErrorString(error));
}

void SoundMgr::playMoveSound()
{
	alSourcePlay(moveSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play move: %s\n",alutGetErrorString(error));
}

void SoundMgr::playMoveSoundPTwo()
{
	alSourcePlay(moveSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play move: %s\n",alutGetErrorString(error));
}

void SoundMgr::stopMoveSound()
{
	alSourceStop(moveSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - stop move: %s\n",alutGetErrorString(error));
}

void SoundMgr::stopMoveSoundPTwo()
{
	alSourceStop(moveSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - stop move: %s\n",alutGetErrorString(error));
}

void SoundMgr::playShootSound()
{
	alSourcePlay(shootSource);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play shoot: %s\n",alutGetErrorString(error));
}

void SoundMgr::playShootSoundPTwo()
{
	alSourcePlay(shootSource2);
	if((error = alutGetError()) != ALUT_ERROR_NO_ERROR)
		fprintf(stderr, "ALUT Error - play shoot: %s\n",alutGetErrorString(error));
}