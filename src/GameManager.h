/*
 * gameManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#pragma once

#include "Manager.h"
#include <OgreMeshManager.h>

class GameManager : public Manager
{
private:
	void createEnts();
	void createSky();
	void createGround();

public:
    explicit GameManager(Engine *engine);
	~GameManager();

    void init() override;
    void tick(float dt) override;
    void loadLevel() override;
    void stop() override;

	Ogre::Plane ocean;
};
