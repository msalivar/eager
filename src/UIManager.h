/*
* UiMgr.h
*
*  Created on: Apr 12, 2017
*      Author: chad
*/

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <string>

#include "Manager.h"
#include <SdkTrays.h>

class UIManager : 
public Manager,
public Ogre::FrameListener,
public OIS::KeyListener,
public OIS::MouseListener,
public Ogre::WindowEventListener,
public OgreBites::SdkTrayListener
{
private:
	void loadMenu();
	std::string stringTime(float time);
	std::string getCredits();

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void buttonHit(OgreBites::Button *b);
	void itemSelected(OgreBites::SelectMenu *m);

public:

	UIManager(Engine *engine);
	~UIManager();
	virtual void init();
	virtual void tick(float dt);
	virtual void loadLevel();
	virtual void loadWinScreen(int id);
	virtual void stop();

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::OverlaySystem* mOverlaySystem;
	OgreBites::Label *timeMonitor;
	OgreBites::Button *creditsButton;
	OgreBites::Button* restartButton;
	OgreBites::TextBox *credits;
	OgreBites::Label* P1ScoreBox;
	OgreBites::Label* P2ScoreBox;
	bool playerOneWin;
	bool playerTwoWin;
};

#endif /* INC_UIMGR_H_ */
