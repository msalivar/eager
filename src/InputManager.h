/*
 * inputManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#pragma once

#include <OgreWindowEventUtilities.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include "Manager.h"
#include "Entity381.h"
#include "Command.h"

class InputManager : 
public Manager,
public OIS::KeyListener,
public OIS::MouseListener,
public Ogre::WindowEventListener,
public OgreBites::SdkTrayListener,
public Ogre::FrameListener
{
private:
	void UpdateCamera(float dt);
	void UpdateDesiredSpeedHeading(float dt);
	void UpdateSelection(float dt);
	void HandleSingleSelection();
	void HandleCommand();
	Ogre::Vector3 GetPositionUnderMouse();
	Entity381* GetClosestEntityToPosition(Ogre::Vector3 position);
	void CommandMoveTo(Ogre::Vector3 position);
	void CommandFollow(Entity381* entity);
	void CommandIntercept(Entity381* entity);
	void AddOrSetCommand(Entity381* ent, Command* command);

	float keyboardTimer;
	float selectionTimer;
	float keyTime;
	float selectionTime;
	Ogre::Vector3 posUnderMouse;
	float selectionDistanceSquaredThreshold;

protected:
    void windowResized(Ogre::RenderWindow *rw) override;
    void windowClosed(Ogre::RenderWindow *rw) override;

    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;
    bool mouseMoved(const OIS::MouseEvent &arg) override;
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

public:
    explicit InputManager(Engine *engine);
	~InputManager(){}
	void init() override;
	void tick(float dt) override;
	void loadLevel() override;
	void stop() override;

	//OIS Input devices
	OIS::InputManager* oisInputManager;
    OIS::Mouse*        mouse;
    OIS::Keyboard*     keyboard;

    // Ogre bites
    OgreBites::SdkTrayManager* trayManager;
    OgreBites::InputContext inputContext;
};
