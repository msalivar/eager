/*
 * gameManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#pragma once

#include "Manager.h"
#include <OgreMeshManager.h>
#include "Entity381.h"

class GameManager : public Manager
{
private:
	void createEnts();
	void createSky();
	void createGround();
	void createLevelOne();
	
	std::list<Entity381*> levelEntities;

public:
    explicit GameManager(Engine *engine);
	~GameManager();

    void init() override;
    void tick(float dt) override;
    void loadLevel() override;
    void stop() override;

	Ogre::Plane ocean;
	Entity381* blueTank;
	Entity381* blueTurret;
	Entity381* redTank;
	Entity381* redTurret;
	int arenaSizeX;
	int arenaSizeZ;
};
