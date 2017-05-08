/*
* EntityManager.h
*
*  Created on: Feb 22, 2017
*      Author: sushil
*/

#pragma once

#include <list>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include "Entity381.h"
#include "Manager.h"

class Engine;

class EntityManager : public Manager
{
public:

	explicit EntityManager(Engine *eng);
	~EntityManager();

	void init() override;
	void tick(float dt) override;
	void loadLevel() override;
	void stop() override;

	Entity381* CreateEntity(EntityType entityType, Ogre::Vector3 pos);
	Entity381* CreateProjectile(Ogre::Vector3 position, float heading, EntityType owner);
	Entity381* CreateWall(Ogre::Vector3 position, float heading);
	Entity381* CreateTower(Ogre::Vector3 position, float heading);
	void CreateOgreEntityAndNode(Entity381 *ent, float scale = 1);
	bool CheckForCollision(Entity381* bullet, Entity381* object, float multiplier = 1);
	void HandleBulletState(Entity381* entity);
	void HandleArenaBounds(Entity381* entity, int arenaSizeX, int arenaSizeZ, float dt);
	void HandleTankLevelCollision(Entity381* entity, float dt);

	std::list<Entity381 *> entities;

};