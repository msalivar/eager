/*
* Entity381.cpp
*
*  Created on: Feb 22, 2017
*      Author: sushil
*/

#include "Entity381.h"
#include "Aspect.h"

int Entity381::nextId = 0;

Entity381::Entity381(EntityType entType, Ogre::Vector3 pos)
{
	this->entityType = entType;
	this->pos = pos;
	this->heading = heading;
	this->vel = Ogre::Vector3::ZERO;
	this->speed = 0;
	this->attachment = nullptr;
	this->bulletCount = 0;
	this->bulletLimit = 3;
	this->reloadTime = 4.0f;
	this->owner = EntityType::NONE;
	this->moving = false;

	if (entityType == EntityType::BULLET)
	{
		this->state = EntityState::ALIVE;
		this->lifeTime = 8.0f;
	}
	else
	{
		this->state = EntityState::NONE;
		this->lifeTime = 0;
	}

	this->aspects.clear();
	Renderable *r = new Renderable(this);
	Physics *p = new Physics(this);

	this->aspects.push_front(r);
	this->aspects.push_front(p);

	this->entityId = Entity381::nextId++;

	DefaultInit();
}

Entity381::~Entity381()
{

}

void Entity381::Tick(float dt)
{
	for (const auto& aspect : aspects)
	{
		aspect->Tick(dt);
	}
	reloadTime -= dt;
	if (reloadTime <= 0)
	{
		reloadTime = 4.0f;
		bulletCount = 0;
	}
}

void Entity381::DefaultInit()
{
	this->acceleration = 8.0f;
	this->deceleration = 14.0f;
	this->reverseAcceleration = 5.0f;
	this->turnRate = 0.2f;

	this->maxSpeed = 35.0f;
	this->minSpeed = -30.0f;

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

Wall::Wall(Ogre::Vector3 pos, float heading) : Entity381(EntityType::WALL, pos)
{
	this->meshfile = "wall.mesh";
	this->heading = heading;
	this->desiredHeading = heading;
}

Wall::~Wall()
{
}

Tower::Tower(Ogre::Vector3 pos, float heading) : Entity381(EntityType::WALL, pos)
{
	this->meshfile = "tower.mesh";
	this->heading = heading;
	this->desiredHeading = heading;
}

Tower::~Tower()
{
}