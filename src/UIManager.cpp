/*
* UiMgr.cpp
*
*  Created on: Apr 12, 2017
*      Author: chad
*/

#include "UIManager.h"
#include "Engine.h"
#include <string>

UIManager::UIManager(Engine* eng) : Manager(eng) {
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	mOverlaySystem = new Ogre::OverlaySystem();
	engine->graphicsManager->ogreSceneManager->addRenderQueueListener(mOverlaySystem);
	mTrayMgr = 0;
	timeMonitor = 0;

	//Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UIManager::~UIManager() { // before gfxMgr destructor

}

void UIManager::init() {
	//init sdktrays

	mInputContext.mKeyboard = engine->inputManager->keyboard;
	mInputContext.mMouse = engine->inputManager->mouse;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->graphicsManager->ogreRenderWindow, mInputContext, this);
	//mTrayMgr->hideCursor();
}

void UIManager::stop() {

}

void UIManager::loadLevel() {
	mTrayMgr->hideCursor();
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Click Me!");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 100, 20, 10);

	//timeMonitor = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Timer", stringTime(engine->gameManager->gameplayTime));
}

void UIManager::tick(float dt) {
	mTrayMgr->refreshCursor();
	//Update the time since last event if in splash screen
	if (engine->currentState == STATE::SPLASH)
	{
		engine->timePassed += dt;
		//If 3 seconds have passed, go into gameplay
		if (engine->timePassed >= 3)
		{
			engine->currentState = STATE::MAIN_MENU;
			engine->graphicsManager->loadMenu();
			engine->soundManager->playMusic(0); // Play menu music
			loadMenu();//Creates the button
		}
	}
	/*else if (engine->currentState == STATE::GAMEPLAY)
	{
		timeMonitor->setCaption(stringTime(engine->gameManager->gameplayTime));
		std::cout << stringTime(engine->gameManager->gameplayTime) << std::endl;
	}*/
}

void UIManager::windowResized(Ogre::RenderWindow* rw) {
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputManager->mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UIManager::windowClosed(Ogre::RenderWindow* rw) {

}

bool UIManager::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UIManager::keyReleased(const OIS::KeyEvent &arg) {
	return true;
}
bool UIManager::mouseMoved(const OIS::MouseEvent &arg) {
	if (mTrayMgr->injectMouseMove(arg)) return true;
	/* normal mouse processing here... */
	return true;
}
bool UIManager::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(arg, id)) return true;
	/* normal mouse processing here... */
	return true;
}
bool UIManager::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	if (mTrayMgr->injectMouseUp(arg, id)) return true;
	/* normal mouse processing here... */
	return true;
}

void UIManager::buttonHit(OgreBites::Button *b) {
	if (b->getName() == "NewGame")
	{
		std::cout << "New Game pressed" << std::endl;
		engine->currentState = STATE::GAMEPLAY;
		engine->loadLevel();
		engine->soundManager->stopMusic(0); // Stop menu music
		mTrayMgr->destroyWidget(b);
	}
}

void UIManager::itemSelected(OgreBites::SelectMenu *m) {
	if (m->getName() == "MyMenu")
	{
		std::cout << "Menu!" << std::endl;
	}
}

void UIManager::loadMenu()
{
	mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "NewGame", "New Game");
}

std::string UIManager::stringTime(float time)
{
	std::string result = "";/*
	int resultTime = (int)time;
	int seconds = resultTime % 60;
	int minutes = resultTime / 60;
	if (minutes < 10)
	{
		result += "0";
	}
	result += std::to_string(minutes) + ":";
	if (seconds < 10)
	{
		result += "0";
	}
	result += std::string(seconds);
	*/
	return result;
}
