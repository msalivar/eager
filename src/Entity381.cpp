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
	this->attachment = nullptr;
	this->bulletCount = 0;
	this->bulletLimit = 3;

	this->aspects.clear();
	Renderable *r = new Renderable(this);
	Physics *p = new Physics(this);
	UnitAI *ai = new UnitAI(this);

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
	this->acceleration = 40;
	this->turnRate = 0.2f;

	this->maxSpeed = 30;
	this->minSpeed = -15;

	this->desiredHeading = this->heading;
	this->desiredSpeed = 0;

	this->meshfile = "cube.mesh";

}

BlueTank::BlueTank(Ogre::Vector3 pos) : Entity381(EntityType::BLUETANK, pos)
{
	this->meshfile = "blueTank.mesh";
	this->heading = 0;
}

BlueTank::~BlueTank()
{
}

RedTank::RedTank(Ogre::Vector3 pos) : Entity381(EntityType::REDTANK, pos)
{
	this->meshfile = "redTank.mesh";
	this->heading = 0;
}

RedTank::~RedTank()
{
}

BlueTurret::BlueTurret(Ogre::Vector3 pos) : Entity381(EntityType::BLUETURRET, pos)
{
	this->meshfile = "blueTurret.mesh";
	this->heading = 0;
}

BlueTurret::~BlueTurret()
{
}

RedTurret::RedTurret(Ogre::Vector3 pos) : Entity381(EntityType::REDTURRET, pos)
{
	this->meshfile = "redTurret.mesh";
	this->heading = 0;
}

RedTurret::~RedTurret()
{
}

Bullet::Bullet(Ogre::Vector3 pos, float heading) : Entity381(EntityType::BULLET, pos)
{
	this->meshfile = "bullet.mesh";
	this->desiredSpeed = 50;
	this->maxSpeed = 50;
	this->speed = 50;
	this->heading = heading;
	this->desiredHeading = heading;
}

Bullet::~Bullet()
{
}
