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

	float pOneMoveTimer;
	float pOneTurnTimer;
	float pOneAimTimer;
	float pOneShootTimer;

	float pTwoMoveTimer;
	float pTwoTurnTimer;
	float pTwoAimTimer;
	float pTwoShootTimer;

	float moveTime;
	float turnTime;
	float aimTime;
	float shootTime;

    bool UpdateLocations(float dt);

protected:
    void windowResized(Ogre::RenderWindow *rw) override;
    void windowClosed(Ogre::RenderWindow *rw) override;
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

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
