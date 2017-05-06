#pragma once

class InputManager;
class EntityManager;
class UIManager;
class GraphicsManager;
class GameManager;

#include "GraphicsManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "Types.h"

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
	SoundMgr* 		    soundManager;

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
