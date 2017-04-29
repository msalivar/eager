/*
 * Entity.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#pragma once

#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include "Types.h"
#include <list>

class Aspect;

class Entity381 {
	
public:
	Entity381(EntityType entityType, Ogre::Vector3 pos);
	~Entity381();
	void Tick(float dt);
	void DefaultInit();

	//static stuff
	static int nextId;
	float maxSpeed, minSpeed;
	float acceleration, turnRate;
	EntityType entityType;
	std::string meshfile;

	//Ogre stuff
	Ogre::Vector3 pos;
	Ogre::Vector3 vel;
	Ogre::SceneNode *ogreSceneNode;
	Ogre::Entity* ogreEntity;
	Entity381* attachment;

	//Engine stuff dynamic
	float speed, heading;
	float desiredSpeed, desiredHeading;
	bool stopCommands;

	//selection
	bool isSelected;

	unsigned int entityId;

	std::list<Aspect*> aspects;
};

class BlueTank : public Entity381 {

public:
	BlueTank(Ogre::Vector3 pos);
	~BlueTank();

};

class RedTank : public Entity381 {

public:
	RedTank(Ogre::Vector3 pos);
	~RedTank();

};

class BlueTurret : public Entity381 {

public:
	BlueTurret(Ogre::Vector3 pos);
	~BlueTurret();

};

class RedTurret : public Entity381 {

public:
	RedTurret(Ogre::Vector3 pos);
	~RedTurret();

};

class Bullet : public Entity381 {

public:
	Bullet(Ogre::Vector3 pos);
	~Bullet();
};
