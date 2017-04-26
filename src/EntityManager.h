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

class EntityManager: public Manager
{
public:

    explicit EntityManager(Engine *eng);
	~EntityManager();

    void init() override;
    void tick(float dt) override;
    void loadLevel() override;
    void stop() override;

	Entity381 *CreateEntity(EntityType entityType, Ogre::Vector3 pos);
	void CreateOgreEntityAndNode(Entity381 *ent);

	std::list<Entity381 *> entities;

};
