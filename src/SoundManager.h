#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreFrameListener.h>

#include <wave.h>
#include <al.h>
#include <alc.h>
#include "Manager.h"
#include <AL/alut.h>

class Entity;


class SoundMgr : public Manager
{
public:
	SoundMgr(Engine* eng);
	~SoundMgr();
	//default methods
	void init();
	void stop();
	void loadLevel();
	void tick(float dt) override {}

	static ALuint 	menuBuffer,   	menuSource,
					musicBuffer1,	musicSource1,
					musicBuffer2, 	musicSource2,
					musicBuffer3, 	musicSource3,
              		idleBuffer,    	idleSource,
              		idleBuffer2,	idleSource2,
              		moveBuffer,     moveSource,
              		moveBuffer2,	moveSource2,
              		shootBuffer,    shootSource,
              		shootBuffer2,	shootSource2;

	static ALenum error;

	void playMusic(int id);
	void stopMusic(int id);

	void playIdleSound();
	void stopIdleSound();
	void playIdleSoundPTwo();
	void stopIdleSoundPTwo();

	void playMoveSound();
	void stopMoveSound();
	void playMoveSoundPTwo();
	void stopMoveSoundPTwo();

	void playShootSound();
	void playShootSoundPTwo();

};
