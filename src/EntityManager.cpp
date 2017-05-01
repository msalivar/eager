/*
 * EntityManager.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "EntityManager.h"
#include "Engine.h"

EntityManager::EntityManager(Engine *eng): Manager(eng)
{
	entities.clear();
}

EntityManager::~EntityManager()
{
}

void EntityManager::tick(float dt)
{
    for(const auto& entity : entities)
    {
        entity->Tick(dt);
    }
}

void EntityManager::init()
{
}

void EntityManager::loadLevel()
{
}

void EntityManager::stop()
{
}

void EntityManager::CreateOgreEntityAndNode(Entity381 *ent, float scale)
{
	if (ent)
	{
		ent->ogreEntity = engine->graphicsManager->ogreSceneManager->createEntity(ent->meshfile);
		ent->ogreSceneNode = 
			engine->graphicsManager->ogreSceneManager->getRootSceneNode()->createChildSceneNode(ent->pos);
		ent->ogreSceneNode->attachObject(ent->ogreEntity);
		ent->ogreSceneNode->scale(scale, scale, scale);
	}
}

Entity381* EntityManager::CreateEntity(EntityType entityType, Ogre::Vector3 position)
{
	Entity381 *ent = 0;
	switch (entityType)
	{
	case EntityType::BLUETANK:
		ent = new BlueTank(position);
		break;
	case EntityType::BLUETURRET:
		ent = new BlueTurret(position);
		break;
	case EntityType::REDTANK:
		ent = new RedTank(position);
		break;
	case EntityType::REDTURRET:
		ent = new RedTurret(position);
		break;
	default:
		ent = new BlueTank(position);
		break;
	}

	CreateOgreEntityAndNode(ent);
	entities.push_front(ent);
	return ent;
}

Entity381* EntityManager::CreateProjectile(Ogre::Vector3 position, float heading)
{
	Entity381 *ent = 0;
	ent = new Bullet(position, heading);
	CreateOgreEntityAndNode(ent, 5);
	entities.push_front(ent);
	return ent;
}