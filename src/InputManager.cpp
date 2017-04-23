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
	keyTime = 0.2f;
	selectionTime = 0.2f;
	keyboardTimer = keyTime;
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
	UpdateDesiredSpeedHeading(dt);
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

bool InputManager::keyPressed(const OIS::KeyEvent &arg)
{
	//std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool InputManager::keyReleased(const OIS::KeyEvent &arg)
{
	//std::cout << "Key Released: " << arg.key << std::endl;
	if (arg.key == OIS::KC_TAB)
	{
		engine->entityManager->SelectNextEntity();
	}
	return true;
}
bool InputManager::mouseMoved(const OIS::MouseEvent &arg)
{
    return true;
}
bool InputManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if (id == OIS::MB_Left)
	{
		//std::cout << "Left mouse pressed" << std::endl;
		HandleSingleSelection();
	}
	else if (id == OIS::MB_Right)
	{
		HandleCommand();
	}
	return true;
}
bool InputManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}

void InputManager::HandleSingleSelection()
{
	OIS::MouseState ms = mouse->getMouseState();
	Ogre::Ray mouseRay = engine->graphicsManager->ogreCamera->getCameraToViewportRay(ms.X.abs / (float)ms.width, ms.Y.abs / (float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gameManager->ocean);
	if (result.first)
	{
		this->posUnderMouse = mouseRay.getPoint(result.second);
		float minDistanceSquared = FLT_MAX;
		float distanceSquared;
		// find ent that is 1. Within threshold distance && 2. Nearest to mouse cursor
		for (std::list<Entity381 *>::const_iterator it = engine->entityManager->entities.begin(); it != engine->entityManager->entities.end(); ++it)
		{
			distanceSquared = this->posUnderMouse.squaredDistance((*it)->pos);
			if (distanceSquared < selectionDistanceSquaredThreshold)
			{
				if (distanceSquared < minDistanceSquared)
				{
					engine->entityManager->selectedEntity->isSelected = false;
					engine->entityManager->selectedEntity = (*it);
					(*it)->isSelected = true;
					minDistanceSquared = distanceSquared;
				}
			}
		}
	}
}

Ogre::Vector3 InputManager::GetPositionUnderMouse() {
	OIS::MouseState ms = mouse->getMouseState();
	Ogre::Ray mouseRay = engine->graphicsManager->ogreCamera->getCameraToViewportRay(ms.X.abs / (float)ms.width, ms.Y.abs / (float)ms.height);
	std::pair<bool, float> result = mouseRay.intersects(engine->gameManager->ocean);
	if (result.first) {
		return mouseRay.getPoint(result.second);
	}
	else {
		return Ogre::Vector3::NEGATIVE_UNIT_Y;
	}
}

Entity381 * InputManager::GetClosestEntityToPosition(Ogre::Vector3 position) {
	Entity381* closest = 0;
	float minDistanceSquared = FLT_MAX;
	float distanceSquared;
	// find ent that is 1. Within threshold distance && 2. Nearest to mouse cursor
	for (std::list<Entity381 *>::const_iterator it = engine->entityManager->entities.begin(); it != engine->entityManager->entities.end(); ++it) {
		distanceSquared = position.squaredDistance((*it)->pos);
		if (distanceSquared < selectionDistanceSquaredThreshold) {
			if (distanceSquared < minDistanceSquared) {
				closest = (*it);
				minDistanceSquared = distanceSquared;
			}
		}
	}
	return closest;
}

void InputManager::HandleCommand()
{
	std::cout << "Handling command" << std::endl;
	if (engine->entityManager->selectedEntity != 0)
	{
		Ogre::Vector3 pos = GetPositionUnderMouse();
		std::cout << "Right Click position: " << pos << std::endl;
		if (pos != Ogre::Vector3::NEGATIVE_UNIT_Y)
		{
			Entity381 *closest = GetClosestEntityToPosition(pos);
			if (closest == 0)
			{
				CommandMoveTo(pos);
			}
			else {
				if (keyboard->isKeyDown(OIS::KC_LCONTROL))
				{
					CommandIntercept(closest);
				}
				else {
					CommandFollow(closest);
				}
			}
		}
	}
}

void InputManager::AddOrSetCommand(Entity381* entity, Command *com)
{
	for (std::list<Aspect*>::const_iterator ai = entity->aspects.begin(); ai != entity->aspects.end(); ++ai)
	{
		if ((*ai)->aspectType == ASPECT_TYPE::AI)
		{
			UnitAI* unitAI = dynamic_cast<UnitAI *> (*ai);
			if (keyboard->isKeyDown(OIS::KC_LSHIFT))
			{
				unitAI->AddCommand(com);
			}
			else
			{
				unitAI->SetCommand(com);
			}
			break;
		}
	}
}

void InputManager::CommandIntercept(Entity381* target)
{
	std::cout << "Intercepting: " << target->meshfile << std::endl;
	Entity381* selectedEntity = engine->entityManager->selectedEntity;
	Intercept *interceptCommand = new Intercept(selectedEntity, target);
	interceptCommand->init();
	AddOrSetCommand(selectedEntity, interceptCommand);
}

void InputManager::CommandFollow(Entity381 *target)
{
	std::cout << "Following: " << target->meshfile << std::endl;
	Entity381* selectedEntity = engine->entityManager->selectedEntity;
	Follow *followCommand = new Follow(selectedEntity, target);
	followCommand->init();
	AddOrSetCommand(selectedEntity, followCommand);
}

void InputManager::CommandMoveTo(Ogre::Vector3 position)
{
	std::cout << "Moving to: " << position << std::endl;
	Entity381* selectedEntity = engine->entityManager->selectedEntity;
	MoveTo* moveToCommand = new MoveTo(selectedEntity, position);
	moveToCommand->init();
	AddOrSetCommand(selectedEntity, moveToCommand);

}

// Game specific input handling
void InputManager::UpdateCamera(float dt)
{
	float move = 100.0f;
	float rotate = 0.1f;

	Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	if (keyboard->isKeyDown(OIS::KC_W))
		dirVec.z -= move;

	if (keyboard->isKeyDown(OIS::KC_S))
		dirVec.z += move;

	if (keyboard->isKeyDown(OIS::KC_E))
		dirVec.y += move;

	if (keyboard->isKeyDown(OIS::KC_F))
		dirVec.y -= move;

	if (keyboard->isKeyDown(OIS::KC_A))
	{
		if (keyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->graphicsManager->cameraNode->yaw(Ogre::Degree(5 * rotate));
		else
			dirVec.x -= move;
	}

	if (keyboard->isKeyDown(OIS::KC_D))
	{
		if (keyboard->isKeyDown(OIS::KC_LSHIFT))
			engine->graphicsManager->cameraNode->yaw(Ogre::Degree(-5 * rotate));
		else
			dirVec.x += move;
	}

	engine->graphicsManager->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);

}

void InputManager::UpdateDesiredSpeedHeading(float dt)
{
	keyboardTimer -= dt;

	if (engine->entityManager->selectedEntity)
	{
		if ((keyboardTimer < 0) && keyboard->isKeyDown(OIS::KC_S))
		{
			keyboardTimer = keyTime;
			engine->entityManager->selectedEntity->stopCommands = true;
		}
	}

}

void InputManager::UpdateSelection(float dt)
{
	selectionTimer -= dt;
	if (selectionTimer < 0 && keyboard->isKeyDown(OIS::KC_TAB))
	{
		selectionTimer = this->selectionTime;
		engine->entityManager->SelectNextEntity();
	}
}