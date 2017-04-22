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

	createEnts();
	createSky();
	createGround();
}

void GameManager::stop()
{

}

void GameManager::tick(float dt)
{

}

void GameManager::createEnts()
{
	Entity381 * ent;
	int x = 0;
	ent = engine->entityManager->CreateEntity(EntityType::DDG, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x + 200;
	ent = engine->entityManager->CreateEntity(EntityType::CIGARETTE, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x + 200;
	ent = engine->entityManager->CreateEntity(EntityType::ALIEN, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x + 200;
	ent = engine->entityManager->CreateEntity(EntityType::CVN, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	x = x + 300;
	ent = engine->entityManager->CreateEntity(EntityType::FRIGATE, Ogre::Vector3(x, 0, 0), 0);
	std::cout << "Created: " << ent->meshfile << std::endl;
	
	engine->entityManager->selectedEntity = ent;
	ent->isSelected = true;
}

void GameManager::createGround()
{
	//Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		ocean,
		15000, 15000, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	Ogre::Entity* groundEntity = engine->graphicsManager->ogreSceneManager->createEntity("ground");
	engine->graphicsManager->ogreSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	//groundEntity->setMaterialName("OceanHLSL_GLSL");
	groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
	//groundEntity->setMaterialName("Ocean2_Cg");
	//groundEntity->setMaterialName("NavyCg");
}

void GameManager::createSky()
{
	engine->graphicsManager->ogreSceneManager->setSkyBox(true, "Examples/StormySkyBox");
}