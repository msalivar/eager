/*
 * Entity381.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "Entity381.h"
#include "Aspect.h"
#include "UnitAI.h"

int Entity381::nextId = 0;

Entity381::Entity381(EntityType entType, Ogre::Vector3 pos)
{
	entityType = entType;
	this->pos = pos;
	this->heading = heading;
	this->vel = Ogre::Vector3::ZERO;
	this->speed = 0;
	this->isSelected = false;
	this->attachment = nullptr;

	this->aspects.clear();
	Renderable *r = new Renderable(this);
	Physics *p = new Physics(this);
	UnitAI *ai = new UnitAI(this);
	stopCommands = false;

	this->aspects.push_front(r);
	this->aspects.push_front(p);
	this->aspects.push_front(ai);

	this->entityId = Entity381::nextId++;

	DefaultInit();
}

Entity381::~Entity381()
{

}

void Entity381::Tick(float dt)
{
    for(const auto& aspect : aspects)
    {
        aspect->Tick(dt);
    }
}

void Entity381::DefaultInit()
{
	this->acceleration = 0.5f;
	this->turnRate = 0.2f;

	this->maxSpeed = 75;
	this->minSpeed = -30;

	this->desiredHeading = this->heading;
	this->desiredSpeed = 0;

	this->meshfile = "cube.mesh";

}

BlueTank::BlueTank(Ogre::Vector3 pos) : Entity381(EntityType::BLUETANK, pos)
{
	this->meshfile = "blueTank.mesh";
	this->maxSpeed = 75;
	this->acceleration = 50;
}

BlueTank::~BlueTank()
{
}

RedTank::RedTank(Ogre::Vector3 pos) : Entity381(EntityType::REDTANK, pos)
{
	this->meshfile = "redTank.mesh";
	this->maxSpeed = 75;
	this->acceleration = 50;
}

RedTank::~RedTank()
{
}

BlueTurret::BlueTurret(Ogre::Vector3 pos) : Entity381(EntityType::BLUETURRET, pos)
{
	this->meshfile = "blueTurret.mesh";
}

BlueTurret::~BlueTurret()
{
}

RedTurret::RedTurret(Ogre::Vector3 pos) : Entity381(EntityType::REDTURRET, pos)
{
	this->meshfile = "redTurret.mesh";
}

RedTurret::~RedTurret()
{
}

Bullet::Bullet(Ogre::Vector3 pos) : Entity381(EntityType::BULLET, pos)
{
	this->meshfile = "cigarette.mesh";
	this->maxSpeed = 30;
}

Bullet::~Bullet()
{
}
