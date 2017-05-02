#include "Aspect.h"
#include "Utils.h"
#include <math.h>

Aspect::Aspect(Entity381 * ent)
{
	this->entity = ent;
	this->aspectType = ASPECT_TYPE::NONE;

}

Aspect::~Aspect()
{

}


Renderable::Renderable(Entity381 * ent) : Aspect(ent)
{
	this->aspectType = ASPECT_TYPE::RENDERABLE;
	return;
}

Renderable::~Renderable()
{

}

void Renderable::Tick(float dt)
{
	entity->ogreSceneNode->setPosition(entity->pos);
	entity->ogreSceneNode->setOrientation(Ogre::Quaternion::IDENTITY);
	entity->ogreSceneNode->yaw(Ogre::Radian(-entity->heading));
	if (entity->entityType == EntityType::BULLET)
	{
		entity->lifeTime -= dt;
		if (entity->lifeTime <= 0)
		{
			entity->destroyFlag = true;
		}
	}
}

Physics::Physics(Entity381 * ent) : Aspect(ent)
{
	this->aspectType = ASPECT_TYPE::PHYSICS;
}

Physics::~Physics()
{

}

void Physics::Tick(float dt)
{
	if (entity->speed < entity->desiredSpeed)
		entity->speed += entity->acceleration * dt;
	else if (entity->speed > entity->desiredSpeed && entity->speed > 0)
		entity->speed -= entity->deceleration * dt;
	else if (entity->speed > entity->desiredSpeed && entity->speed <= 0)
		entity->speed -= entity->reverseAcceleration * dt;

	entity->vel = Ogre::Vector3(cos(entity->heading) * entity->speed, 0, sin(entity->heading) * entity->speed);
	entity->pos += entity->vel * dt;
	if (entity->attachment != nullptr)
	{
		entity->attachment->pos = entity->pos;
	}	
}

