#pragma once

#include "Entity381.h"
#include <OgreVector3.h>

class Command {

public:
	Command(Entity381* ent, COMMAND_TYPE ct);
	virtual ~Command();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	Entity381* entity;
	COMMAND_TYPE commandType;

};

class MoveTo : public Command {

public:
	MoveTo(Entity381* ent, Ogre::Vector3 location);
	~MoveTo();

	void init();
	void tick(float dt);
	bool done();

	Ogre::Vector3 targetLocation;
	float MOVE_DISTANCE_THRESHOLD;

};

class Follow : public Command {
public:
	Follow(Entity381* ent, Entity381* targ);
	~Follow();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	virtual Ogre::Vector3 ComputeTargetLocation();

	Entity381* target;
	float FOLLOW_DISTANCE;

};

class Intercept : public Follow {
public:
	Intercept(Entity381* ent, Entity381* targ);
	~Intercept();

	virtual void init();
	virtual void tick(float dt);
	virtual bool done();

	virtual Ogre::Vector3 ComputeInterceptLocation();
	void runIntercept();

};
