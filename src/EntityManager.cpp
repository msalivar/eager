/*
 * EntityManager.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "EntityManager.h"
#include "Engine.h"
#include <string.h>

EntityManager::EntityManager(Engine *eng) : Manager(eng)
{
    entities.clear();
}

EntityManager::~EntityManager()
{
    entities.clear();
}

void EntityManager::tick(float dt)
{
	if (engine->currentState != STATE::GAMEPLAY) { return; }
    // some serious stuff going on here
    for (const auto& entity : entities)
    {
        // Bullet specific effects
        if (entity->entityType == EntityType::BULLET)
        {
            HandleBulletState(entity);
        }

        // TODO: remove this temporary fix - need a better solution for leftover bullets
        if (entity->state == EntityState::DEAD) { continue; }

        // Tick aspects
        entity->Tick(dt);

        // Handle tank moving sounds
        if (!entity->moving && entity->speed != 0)
        {
            if (entity->entityType == EntityType::BLUETANK)
            {                
                engine->soundManager->stopIdleSound();
                engine->soundManager->playMoveSound();
            }
            else if (entity->entityType == EntityType::REDTANK)
            {
                engine->soundManager->stopIdleSoundPTwo();
                engine->soundManager->playMoveSoundPTwo();
            }
            entity->moving = true;
        }
        else if (entity->moving && entity->speed == 0)
        {
            if (entity->entityType == EntityType::BLUETANK)
            {
                engine->soundManager->stopMoveSound();
                engine->soundManager->playIdleSound();
            }
            else if (entity->entityType == EntityType::REDTANK)
            {
                engine->soundManager->stopMoveSoundPTwo();
                engine->soundManager->playIdleSoundPTwo();
            }
            entity->moving = false;
        }

        // Check entity bounds
        if (entity->entityType == EntityType::BULLET)
        {
            HandleArenaBounds(entity, engine->gameManager->arenaSizeX, engine->gameManager->arenaSizeZ, dt);
        }
        if (entity->entityType == EntityType::BLUETANK ||
            entity->entityType == EntityType::REDTANK)
        {
            HandleArenaBounds(entity, engine->gameManager->arenaSizeX, engine->gameManager->arenaSizeZ, dt);
            HandleTankLevelCollision(entity, dt);
        }
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
        ent->ogreEntity = 
            engine->graphicsManager->ogreSceneManager->createEntity(
                std::to_string(Entity381::nextId),
                ent->meshfile);
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

Entity381* EntityManager::CreateProjectile(Ogre::Vector3 position, float heading, EntityType owner)
{
    Entity381 *ent = 0;
    ent = new Bullet(position, heading);
    CreateOgreEntityAndNode(ent, 5);
    entities.push_front(ent);
    ent->owner = owner;
    return ent;
}

Entity381* EntityManager::CreateWall(Ogre::Vector3 position, float heading)
{
    Entity381 *ent = 0;
    ent = new Wall(position, heading);
    CreateOgreEntityAndNode(ent, 5);
    entities.push_front(ent);
    return ent;
}

Entity381* EntityManager::CreateTower(Ogre::Vector3 position, float heading)
{
    Entity381 *ent = 0;
    ent = new Tower(position, heading);
    CreateOgreEntityAndNode(ent, 20);
    entities.push_front(ent);
    return ent;
}

bool EntityManager::CheckForCollision(Entity381* bullet, Entity381* object, float multiplier)
{
    Ogre::Real distance = bullet->pos.distance(object->pos);
    return distance <= object->ogreEntity->getBoundingRadius() * multiplier;
}

void EntityManager::HandleBulletState(Entity381* entity)
{
    // Check for bullet collision
    if (entity->state == EntityState::ALIVE)
    {
        if (entity->owner == EntityType::REDTANK &&
            CheckForCollision(entity, engine->gameManager->blueTank))
        {
            entity->state = EntityState::DESTROY;
            engine->soundManager->playDestroySound();
            engine->gameManager->pTwoScore++;
			// Check for win here
			if (engine->gameManager->pTwoScore >= 3)
			{
				engine->currentState = STATE::WIN_SCREEN;
				engine->uiManager->loadWinScreen(2);
		    }
		}
        else if (entity->owner == EntityType::BLUETANK &&
            CheckForCollision(entity, engine->gameManager->redTank))
        {
            entity->state = EntityState::DESTROY;
            engine->soundManager->playDestroySound();
            engine->gameManager->pOneScore++;
            // Check for win here
			if (engine->gameManager->pOneScore >= 3)
			{
				engine->currentState = STATE::WIN_SCREEN;
				engine->uiManager->loadWinScreen(1);
		    }
        }        
        // check level entities for collision
        for (const auto& object : engine->gameManager->levelEntities)
        {
            // this multiplier is for towers only - temp fix
            if (CheckForCollision(entity, object, 6))
            {
                entity->state = EntityState::DESTROY;
                break;
            }
        }
    }
    // Check for destroy flag
    if (entity->state == EntityState::DESTROY)
    {
        entity->aspects.clear();
        engine->graphicsManager->ogreSceneManager->destroyEntity(entity->ogreEntity);
        entity->ogreEntity = nullptr;
        entity->ogreSceneNode = nullptr;
        if (entity->attachment != nullptr)
        {
            entity->attachment->state = EntityState::DESTROY;
        }
        entity->state = EntityState::DEAD;
    }
}

void EntityManager::HandleArenaBounds(Entity381* entity, int arenaSizeX, int arenaSizeZ, float dt)
{
    // Check bounds
    if (entity->pos.x >= arenaSizeX || entity->pos.x <= -arenaSizeX ||
        entity->pos.z >= arenaSizeZ || entity->pos.z <= -arenaSizeZ)
    {
        if (entity->entityType == EntityType::BULLET)
        {
            entity->state = EntityState::DESTROY;
        }
        else if (entity->entityType == EntityType::BLUETANK
            || entity->entityType == EntityType::REDTANK)
        {
            entity->speed = 0;
            entity->desiredSpeed = 0;
            // Move tank towards middle slowly
            Ogre::Vector3 dirToMiddle = Ogre::Vector3(0, 0, 1) - entity->pos;
            entity->pos += dirToMiddle * dt;
        }
    }
}

void EntityManager::HandleTankLevelCollision(Entity381* entity, float dt)
{
    for (const auto& object : engine->gameManager->levelEntities)
    {
        if (CheckForCollision(entity, object, 6))
        {
            entity->speed = 0;
            entity->desiredSpeed = 0;
            // Move tank out slowly
            Ogre::Vector3 dir = entity->pos - object->pos;
            entity->pos += dir * dt;
        }        
    }
}
