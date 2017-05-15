/*
 * gameManager.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#include "GameManager.h"
#include "Engine.h"
#include <OgreMeshManager.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameManager::GameManager(Engine *engine): Manager(engine)
{
	ocean = Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
	gameplayTime = 0;
	pOneScore = 0;
	pTwoScore = 0;
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
}

void GameManager::loadLevel()
{
	//We know graphicsMgr is ready and initialized
	engine->graphicsManager->ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = engine->graphicsManager->ogreSceneManager->createLight("MainLight");
	light->setPosition(0.0, 200.0, 0.0);

	createGround();
	createSky();
	createEnts();
	createArena();

	/* initialize random seed: */
	srand (time(NULL));

	/* generate random number between 1 and 3: */
	int num = rand() % 3 + 1;
	engine->soundManager->playMusic(num);

	/* generate random number between 1 and 3: */
	createLevelThree();
	// num = rand() % 3 + 1;
	// if (num == 1) { createLevelOne(); }
	// else if (num == 2) { createLevelTwo(); }
	// else if (num == 3) { createLevelThree(); }

	this->loadObjects();
}

void GameManager::stop()
{
}

void GameManager::tick(float dt)
{
	// ADDED CODE
	if (engine->currentState == STATE::GAMEPLAY)
	{
		gameplayTime += dt;
		//std::cout << "Gameplay time: " << gameplayTime << std::endl;
}
}

void GameManager::createEnts()
{
	blueTank = engine->entityManager->CreateEntity(EntityType::BLUETANK, Ogre::Vector3(200, 0, 100));
	blueTurret = engine->entityManager->CreateEntity(EntityType::BLUETURRET, Ogre::Vector3(200, 0, 100));
	blueTank->attachment = blueTurret;
	blueTank->heading = 3.14159f;
	blueTurret->heading = 3.14159f;

	redTank = engine->entityManager->CreateEntity(EntityType::REDTANK, Ogre::Vector3(-200, 0, -100));
	redTurret = engine->entityManager->CreateEntity(EntityType::REDTURRET, Ogre::Vector3(-200, 0, -100));
	redTank->attachment = redTurret;

	//Ogre::Real radius = blueTank->ogreEntity->getBoundingRadius();
	//Ogre::AxisAlignedBox box = blueTank->ogreEntity->getBoundingBox();
	return;
}

void GameManager::createGround()
{
	//Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		ocean,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = engine->graphicsManager->ogreSceneManager->createEntity("ground");
	engine->graphicsManager->ogreSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/GrassFloor");
}

void GameManager::createSky()
{
	engine->graphicsManager->ogreSceneManager->setSkyBox(true, "Examples/StormySkyBox");
}

void GameManager::loadObjects()
{
	// Create Entity
	Ogre::Entity *splash = engine->graphicsManager->ogreSceneManager->createEntity("Splash.mesh");

	// Create scene node for this entity
	engine->graphicsManager->splashNode = engine->graphicsManager->ogreSceneManager->getRootSceneNode()->createChildSceneNode();
	engine->graphicsManager->splashNode->attachObject(splash);
	splash->setMaterialName("Material");
	engine->graphicsManager->splashNode->setScale(10.f, 10.0f, 10.0f);
	engine->graphicsManager->splashNode->setPosition(0.0f, 400, -3500);
	engine->graphicsManager->splashNode->roll(Ogre::Degree(-360));
	engine->graphicsManager->splashNode->pitch(Ogre::Degree(90));
}

void GameManager::restart()
{
    pOneScore = 0;
    pTwoScore = 0;

	blueTank->pos = Ogre::Vector3(200, 0, 100);
	blueTurret->pos = Ogre::Vector3(200, 0, 100);
    blueTank->speed = 0; blueTank->desiredSpeed = 0;
    blueTank->heading = 3.14159f;	
    blueTurret->heading = 3.14159f;

	redTank->pos = Ogre::Vector3(-200, 0, -100);
	redTurret->pos = Ogre::Vector3(-200, 0, -100);
    redTank->speed = 0; redTank->desiredSpeed = 0;
    redTank->heading = 0;
	redTurret->heading = 0;
    
    // delete all bullets
    for (const auto& entity : engine->entityManager->entities)
    {
        if (entity->entityType == EntityType::BULLET
            && entity->state != EntityState::DEAD)
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
	engine->currentState = STATE::GAMEPLAY;
	/* initialize random seed: */
	srand (time(NULL));
	/* generate random number between 1 and 3: */
	int num = rand() % 3 + 1;
	engine->soundManager->playMusic(num);
	// make random level
	clearLevel();
	num = rand() % 3 + 1;
	if (num == 1) { createLevelOne(); }
	else if (num == 2) { createLevelTwo(); }
	else if (num == 3) { createLevelThree(); }
}

void GameManager::createArena()
{
	int buffer = 20;
	int increment = 75;
	arenaSizeX = 275;
	arenaSizeZ = 175;
	Entity381 *ent;
	// left walls
	int z = 20;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX + buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX + buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX + buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX + buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX + buffer, 0, arenaSizeZ - z), 0);
	// right walls
	z = 20;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(-arenaSizeX - buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(-arenaSizeX - buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(-arenaSizeX - buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(-arenaSizeX - buffer, 0, arenaSizeZ - z), 0); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(-arenaSizeX - buffer, 0, arenaSizeZ - z), 0);
	// top walls
	z = 15;
	increment = 74;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, arenaSizeZ + buffer), 1.5708f);
	// bottom walls
	z = 15;
	increment = 74;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f); z += increment;
	ent = engine->entityManager->CreateWall(Ogre::Vector3(arenaSizeX - z, 0, -arenaSizeZ - buffer + 5), 1.5708f);	
}

void GameManager::clearLevel()
{
	for (const auto& entity : levelEntities)
    {
        entity->aspects.clear();
        engine->graphicsManager->ogreSceneManager->destroyEntity(entity->ogreEntity);
        entity->ogreEntity = nullptr;
        entity->ogreSceneNode = nullptr;
        entity->state = EntityState::DEAD;
    }
	levelEntities.clear();
}

void GameManager::createLevelOne()
{
	Entity381 *ent;
	// towers
	ent = engine->entityManager->CreateTower(Ogre::Vector3(100, -5, -50), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(-100, -5, 50), 0);
	levelEntities.push_front(ent);
}

void GameManager::createLevelTwo()
{
	Entity381 *ent;
	ent = engine->entityManager->CreateTower(Ogre::Vector3(150, -5, 0), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(-150, -5, 0), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, 100), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, -100), 0);
	levelEntities.push_front(ent);
}

void GameManager::createLevelThree()
{
	Entity381 *ent;
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, 170), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, 60), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, -60), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(0, -5, -170), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(160, -5, 0), 0);
	levelEntities.push_front(ent);
	ent = engine->entityManager->CreateTower(Ogre::Vector3(-160, -5, 0), 0);
	levelEntities.push_front(ent);
}