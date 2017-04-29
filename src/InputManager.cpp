/*
 * inputManager.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#include "InputManager.h"
#include "Engine.h"
#include "Aspect.h"
#include "UnitAI.h"

#include <cfloat>
#include <string>
#include <iostream>
#include <sstream>
#include <ostream>

InputManager::InputManager(Engine *engine) : Manager(engine)
{
	keyTime = 0.05f;
	selectionTime = 0.2f;
	pOneKeyboardTimer = keyTime;
	pTwoKeyboardTimer = keyTime;
	selectionTimer = selectionTime;
	selectionDistanceSquaredThreshold = 10000;

    keyboard = nullptr;
    mouse = nullptr;
    oisInputManager = nullptr;

    OIS::ParamList pl;
    size_t windowHandle = 0;
    std::ostringstream windowHandleStr;
    engine->graphicsManager->ogreRenderWindow->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleStr << windowHandle;

    pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));

    // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
    // show or hide the mouse on windows
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE"))); // show
    //pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_EXCLUSIVE"))); // hide
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

    oisInputManager = OIS::InputManager::createInputSystem(pl);
    keyboard = static_cast<OIS::Keyboard*>(oisInputManager->createInputObject(OIS::OISKeyboard, true));
    mouse = static_cast<OIS::Mouse*>(oisInputManager->createInputObject(OIS::OISMouse, true));

    keyboard->setEventCallback(this);
    mouse->setEventCallback(this);

    InputManager::windowResized(engine->graphicsManager->ogreRenderWindow);
    Ogre::WindowEventUtilities::addWindowEventListener(engine->graphicsManager->ogreRenderWindow, this);

    // Input context
    inputContext.mMouse = mouse;
    inputContext.mKeyboard = keyboard;

    // Uncomment to show the OGRE SDK Tray Manager cursor
    //trayManager = new OgreBites::SdkTrayManager("InterfaceName", engine->graphicsManager->ogreRenderWindow, inputContext, this);
    //trayManager->showCursor();

    engine->graphicsManager->ogreRoot->addFrameListener(this);
}

void InputManager::init()
{

}

void InputManager::loadLevel()
{

}

void InputManager::tick(float dt)
{
	keyboard->capture();
	mouse->capture();
	if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		engine->stop();

	UpdateCamera(dt);
	UpdateLocations(dt);
	//UpdateSelection(dt);
}

void InputManager::stop()
{
    if (oisInputManager)
	{
        oisInputManager->destroyInputObject(mouse);
        oisInputManager->destroyInputObject(keyboard);
        OIS::InputManager::destroyInputSystem(oisInputManager);
        oisInputManager = nullptr;
    }
}

void InputManager::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void InputManager::windowClosed(Ogre::RenderWindow* rw)
{
    //Ogre::WindowEventUtilities::removeWindowEventListener(engine->graphicsManager->ogreRenderWindow, this);
    if (rw == engine->graphicsManager->ogreRenderWindow)
	{
        engine->stop();
    }
}

bool InputManager::UpdateLocations(float dt)
{
	float moveSpeed = 4;
	float turnSpeed = 0.02f;

	pOneKeyboardTimer -= dt;
	pTwoKeyboardTimer -= dt;	

	// PLAYER 1
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_W))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTank->desiredSpeed += moveSpeed;
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_A))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTank->heading -= turnSpeed;	
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_S))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTank->desiredSpeed -= moveSpeed;	
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_D))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTank->heading += turnSpeed;
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_Y))
	{
		pOneKeyboardTimer = keyTime;		
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_G))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTurret->heading -= turnSpeed;
	}
	if((pOneKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_J))
	{
		pOneKeyboardTimer = keyTime;
		engine->gameManager->blueTurret->heading += turnSpeed;		
	}

	// PLAYER 2
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_UP))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTank->desiredSpeed += moveSpeed;		
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_LEFT))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTank->heading -= turnSpeed;			
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_DOWN))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTank->desiredSpeed -= moveSpeed;		
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_RIGHT))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTank->heading += turnSpeed;		
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD8))
	{
		pTwoKeyboardTimer = keyTime;		
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD4))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTurret->heading -= turnSpeed;		
	}
	if((pTwoKeyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_NUMPAD6))
	{
		pTwoKeyboardTimer = keyTime;
		engine->gameManager->redTurret->heading += turnSpeed;		
	}

	return true;
}

bool InputManager::keyPressed(const OIS::KeyEvent &arg) {
	return true;
}
bool InputManager::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool InputManager::mouseMoved(const OIS::MouseEvent &arg){
	return true;
}
bool InputManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	return true;
}
bool InputManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
	return true;
}

// Game specific input handling
void InputManager::UpdateCamera(float dt)
{
	float move = 100.0f;
	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (keyboard->isKeyDown(OIS::KC_1))
		dirVec.z -= move;

	if (keyboard->isKeyDown(OIS::KC_2))
		dirVec.z += move;

	if (keyboard->isKeyDown(OIS::KC_3))
		dirVec.x -= move;

	if (keyboard->isKeyDown(OIS::KC_4))
		dirVec.x += move;

	if (keyboard->isKeyDown(OIS::KC_5))
		dirVec.y += move;

	if (keyboard->isKeyDown(OIS::KC_6))
		dirVec.y -= move;

	engine->graphicsManager->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}
