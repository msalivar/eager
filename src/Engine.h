/*
 * engine.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#pragma once

class InputManager;

#include "GraphicsManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Types.h"

class EntityManager;

class Engine
{
public:
	Engine();
	~Engine();

	UIManager*          uiManager;
	EntityManager*      entityManager;
	GraphicsManager*    graphicsManager;
	InputManager*       inputManager;
	GameManager*        gameManager;

	void initialize();
	void run() const;
	void tick_all(float dt) const;
	void stop();
	void shutdown() const;
	void loadLevel();

	bool keepRunning;

	STATE currentState;

	float timePassed;
};
