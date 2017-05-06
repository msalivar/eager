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

private:

public:
	SoundMgr(Engine* eng);
	~SoundMgr();
	//default methods
	void init();
	void stop();
	void loadLevel();
	void tick(float dt) override {}

	static ALuint 	backgroundBuffer,   backgroundSource,
              		idleBuffer,    	 	idleSource,
              		moveBuffer,     	moveSource,
              		shootBuffer,    	shootSource;

	static ALenum error;

	void playBackgroundSound();
	void playIdleSound();
	void playMoveSound();
	void playShootSound();
	void closeAudio();

};
