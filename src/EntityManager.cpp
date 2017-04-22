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

void EntityManager::CreateOgreEntityAndNode(Entity381 *ent)
{

	if (ent)
	{
		ent->ogreEntity = engine->graphicsManager->ogreSceneManager->createEntity(ent->meshfile);
		ent->ogreSceneNode = engine->graphicsManager->ogreSceneManager->getRootSceneNode()->createChildSceneNode(ent->pos);
		ent->ogreSceneNode->attachObject(ent->ogreEntity);
		ent->ogreSceneNode->yaw(Ogre::Radian(ent->heading));
	}

}

Entity381* EntityManager::CreateEntity(EntityType entityType, Ogre::Vector3 position, float heading)
{

	Entity381 *ent = 0;// = new Entity381(entityType, position, heading);
	switch (entityType)
	{
	case EntityType::ALIEN:
		ent = new Alien(position, heading);
		break;
	case EntityType::CIGARETTE:
		ent = new Cigarette(position, heading);
		break;
	case EntityType::DDG:
		ent = new Ddg(position, heading);
		break;
	case EntityType::CVN:
		ent = new Cvn(position, heading);
		break;
	case EntityType::FRIGATE:
		ent = new Frigate(position, heading);
		break;
	default:
		ent = new Ddg(position, heading);
		break;
	}

	CreateOgreEntityAndNode(ent);
	entities.push_front(ent);
	return ent;
}

void EntityManager::SelectNextEntity()
{
	int n = 0;

	for (std::list<Entity381 *>::const_iterator it = entities.begin(); it != entities.end(); ++it)
	{
		n++;
		if ((*it)->isSelected) {
			(*it)->isSelected = false;
			it++;
			if (it == entities.end()) {
				std::cout << "End of ents" << std::endl;
				selectedEntity = *(entities.begin());
			}
			else {
				selectedEntity = *it;
				std::cout << "End of ents" << std::endl;
			}
			selectedEntity->isSelected = true;
			break;
		}
	}

}