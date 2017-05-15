/*
 * graphicsManager.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#include "GraphicsManager.h"
#include "Engine.h"

int GraphicsManager::explosionId = 0;

GraphicsManager::GraphicsManager(Engine *eng): Manager(eng)
{
	rect = NULL;
	backgroundNode = NULL;

#ifdef _DEBUG
	resources = "resources_d.cfg";
	plugins   = "plugins_d.cfg";
#else*/
	resources = "resources.cfg";
	plugins   = "plugins.cfg";
#endif

	ogreRoot = new Ogre::Root(plugins);

	cf.load(resources);
	loadConfig(cf);
	configureRenderSystem();
	ogreRenderWindow = ogreRoot->initialise(true, "Team 7 - Clash of Tanks");
	createSceneManager();
	createCamera();
	createViewport();

    raySceneQuery = ogreSceneManager->createRayQuery(Ogre::Ray());

}

void GraphicsManager::loadConfig(Ogre::ConfigFile cf) const
{
	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while(secIt.hasMoreElements()){
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for(it = settings->begin(); it != settings->end(); ++it){
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}

void GraphicsManager::configureRenderSystem() const
{
	if(!(ogreRoot->restoreConfig() || ogreRoot->showConfigDialog()))
		engine->stop();
}

void GraphicsManager::initResources()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void GraphicsManager::createSceneManager()
{
	ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
    //overlaySystem = new Ogre::OverlaySystem();
    //ogreSceneManager->addRenderQueueListener(overlaySystem);
}

void GraphicsManager::createCamera()
{
	ogreCamera = ogreSceneManager->createCamera("MainCam");
	ogreCamera->setPosition(0, 0, 0);
	ogreCamera->setNearClipDistance(5);
	cameraNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
	pitchNode = cameraNode->createChildSceneNode();
	pitchNode->attachObject(ogreCamera);
	cameraNode->setPosition(0, 500, 0);
	ogreCamera->lookAt(0, 0, 1);
}

void GraphicsManager::createViewport()
{
	ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
	ogreViewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	ogreCamera->setAspectRatio(Ogre::Real(ogreViewport->getActualWidth()) /
											Ogre::Real(ogreViewport->getActualHeight()));

	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("tank.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(true);

	// Create background rectangle covering the whole screen
	rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("Background");

	// Render the background before everything else
	rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	rect->setBoundingBox(aabInf);

	// Attach background to the scene
	backgroundNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode("Background");
	backgroundNode->attachObject(rect);
}

void GraphicsManager::testScene() const
{
	Ogre::Entity *ent = ogreSceneManager->createEntity("ogrehead.mesh");
	Ogre::SceneNode* node = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = ogreSceneManager->createLight("MainLight");
	light->setPosition(20, 80, 50);
	std::cout << "Test scene done" << std::endl;
}

void GraphicsManager::createExplosion(Ogre::Vector3 pos)
{
	// create a particle system named explosions using the explosionTemplate
    Ogre::ParticleSystem* particleSystem = ogreSceneManager->createParticleSystem(std::to_string(explosionId), "explosionTemplate");
    explosionId++;
     
    // fast forward to the point where the particle has been emitted
    particleSystem->fastForward(2.4);
    
    // attach the particle system to a scene node    
	Ogre::Vector3 vec = pos;
	vec.y += 5;
	ogreSceneManager->getRootSceneNode()->createChildSceneNode(vec)->attachObject(particleSystem);
}

GraphicsManager::~GraphicsManager()
{
	delete ogreRoot; //after inputManager destructor
	delete rect; 
	rect = NULL;
}

void GraphicsManager::init()
{
	initResources();
}

void GraphicsManager::loadLevel()
{
	backgroundNode->detachObject(rect); 
}

void GraphicsManager::tick(float dt)
{
	Ogre::WindowEventUtilities::messagePump();
	if(!ogreRoot->renderOneFrame()) engine->stop();
}

void GraphicsManager::stop()
{
	ogreRoot->shutdown();
}

void GraphicsManager::loadMenu()
{
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MenuScreen", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("tank.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	rect->setMaterial("MenuScreen");
}

void GraphicsManager::loadSplashScreen()
{
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("TestScreen", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("test.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	rect->setMaterial("TestScreen");
}

void GraphicsManager::loadWinScreenPlayerOne()
{
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("WinScreen1", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("blueTankVictory.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	rect->setMaterial("WinScreen1");
}

void GraphicsManager::loadWinScreenPlayerTwo()
{
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("WinScreen2", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("redTankVictory.png");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

	rect->setMaterial("WinScreen2");
}