/*
 * gameManager.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#include "GameManager.h"
#include "Engine.h"

GameManager::GameManager(Engine *engine): Manager(engine)
{
	ocean = Ogre::Plane(Ogre::Vector3::UNIT_Y, 0);
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
	light->setPosition(20.0, 80.0, 50.0);

	createGround();
	createSky();
	createEnts();
}

void GameManager::stop()
{
}

void GameManager::tick(float dt)
{
}

void GameManager::createEnts()
{
	blueTank = engine->entityManager->CreateEntity(EntityType::BLUETANK, Ogre::Vector3(-100, 0, 0));
	blueTurret = engine->entityManager->CreateEntity(EntityType::BLUETURRET, Ogre::Vector3(-100, 0, 0));
	blueTank->attachment = blueTurret;
	redTank = engine->entityManager->CreateEntity(EntityType::REDTANK, Ogre::Vector3(100, 0, 0));
	redTurret = engine->entityManager->CreateEntity(EntityType::REDTURRET, Ogre::Vector3(100, 0, 0));
	redTank->attachment = redTurret;
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
	groundEntity->setMaterialName("Examples/Rocky");
}

void GameManager::createSky()
{
	engine->graphicsManager->ogreSceneManager->setSkyBox(true, "Examples/StormySkyBox");
}
