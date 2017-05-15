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
	creditsButton = 0;
	credits = 0;
	controlsButton = 0;
	controls = 0;

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

	P1ScoreBox = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "P1ScoreBox", "Player 1 Score: ", 240);
	P2ScoreBox = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "P2ScoreBox", "Player 2 Score: ", 240);
}

void UIManager::loadWinScreen(int id)
{

	int width = engine->graphicsManager->ogreRenderWindow->getWidth();
	int height = engine->graphicsManager->ogreRenderWindow->getHeight();

	if (id == 1)
	{
		engine->graphicsManager->loadWinScreenPlayerOne();
	}
	else if (id == 2)
	{
		engine->graphicsManager->loadWinScreenPlayerTwo();
	}
	else
	{
		return;
	}

	mTrayMgr->showCursor();

	// Credits Screen Button Select
	creditsButton = mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "CreditsButton", "Credits");
	credits = mTrayMgr->createTextBox(OgreBites::TL_NONE, "Credits", "Credits:", 300, 600);
	credits->getOverlayElement()->setPosition(width - 300, height - 50 - 600);
	credits->setText(getCredits());

	credits->hide();
	credits->setText(getCredits());

	// Restart Button
	restartButton = mTrayMgr->createButton(OgreBites::TL_CENTER, "RestartButton", "Restart", 240);
}

std::string UIManager::getCredits()
{
	return "Clash of Tanks\n\nPresented by Team 7\n\nBrittany Sievert\n\nMatt Salivar\n";
}

void UIManager::tick(float dt) {
	mTrayMgr->refreshCursor();
	//Update the time since last event if in splash screen
	if (engine->currentState == STATE::SPLASH)
	{
		engine->graphicsManager->loadSplashScreen();
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

	else if (engine->currentState == STATE::GAMEPLAY)
	{
		int currentPlayerOneScore = engine->gameManager->pOneScore;
		int currentPlayerTwoScore = engine->gameManager->pTwoScore;
		P1ScoreBox->setCaption("Player 1 Score: " + std::to_string(currentPlayerOneScore));
		P2ScoreBox->setCaption("Player 2 Score: " + std::to_string(currentPlayerTwoScore));
	}

	else if (engine->currentState == STATE::WIN_SCREEN)
	{
		//loadWinScreen();
	}
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
		engine->soundManager->stopMusic(); // Stop menu music
		engine->loadLevel();
		mTrayMgr->destroyWidget(b);
		mTrayMgr->destroyWidget(controls);
		mTrayMgr->destroyWidget(controlsButton);
		controlsButton = NULL;
		controls = NULL;
	}

	else if (b->getName() == "CreditsButton")
	{
		if (credits->isVisible())
		{
			credits->hide();
		}
		else
		{
			credits->setText(getCredits());
			credits->show();
		}
	}

	else if (b->getName() == "RestartButton")
	{
		engine->soundManager->stopMusic(); // Stop win music
		engine->gameManager->restart();
		mTrayMgr->destroyWidget(b);
		mTrayMgr->destroyWidget(creditsButton);
		mTrayMgr->destroyWidget(credits);		
	}

	else if (b->getName() == "ControlButton")
	{
		if (controls->isVisible())
		{
			controls->hide();
		}
		else
		{
			controls->setText(getControls());
			controls->show();
		}
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
	controlsButton = mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT, "ControlButton", "Controls");
	controls = mTrayMgr->createTextBox(OgreBites::TL_NONE, "Controls", "Controls", 300, 550);
	controls->getOverlayElement()->setPosition(0, 450);
	controls->setText(getControls());

	controls->hide();
	controls->setText(getControls());
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

std::string UIManager::getControls()
{
	return "Player 1:\nWASD: Move Tank\nG/J: Move Turret\nY: Shoot\n\nPlayer 2:\nArrow Keys: Move Tank\nNum 4/Num 6: Move Turret\nNum 8: Shoot";
}
