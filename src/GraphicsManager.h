/*
 * GxfManager.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#pragma once

#include "Manager.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <SdkTrays.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

class GraphicsManager : public Manager
{

public:
    explicit GraphicsManager(Engine *eng);
	~GraphicsManager();

    void tick(float dt) override;
    void init() override;
    void loadLevel() override;
    void stop() override;

	void loadMenu();
	void loadSplashScreen();
	void loadWinScreenPlayerOne();
	void loadWinScreenPlayerTwo();

	void testScene() const;

	//Ogre variables
	Ogre::Root *ogreRoot;

	Ogre::String resources;
	Ogre::String plugins;
	Ogre::ConfigFile cf;
	Ogre::Camera* ogreCamera;
	Ogre::RenderWindow* ogreRenderWindow;
	Ogre::SceneManager* ogreSceneManager;
	Ogre::SceneNode *cameraNode, *pitchNode;
    Ogre::OverlaySystem* overlaySystem;

	Ogre::Rectangle2D* rect;
	Ogre::SceneNode* backgroundNode;
	Ogre::SceneNode* splashNode;

	void createExplosion(Ogre::Vector3 pos);

private:

	static int explosionId;

	void loadConfig(Ogre::ConfigFile cf) const;
	void configureRenderSystem() const;
    void initResources();

	void createSceneManager();
	void createCamera();

	Ogre::Viewport *ogreViewport;
	void createViewport();

    // Ray Casting
    Ogre::RaySceneQuery* raySceneQuery;
};
