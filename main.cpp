#include<iostream>
#include<cstdlib>
#include<string>
#include<httplib.h>
#include<nlohmann/json.hpp>
#include"PointCloud.h"
#include"OgreApplicationContext.h"

class Test : public OgreBites::ApplicationContext
{
private:
    Ogre::Root* root;
    Ogre::SceneManager* scnMgr;

    Ogre::RTShader::ShaderGenerator* shadergen;
    Ogre::RenderWindow* renderWid;
    Ogre::SceneNode* charNode;

public:
    Test();
    void setup();
    void test();
};

Test::Test() : OgreBites::ApplicationContext("Ogre_Test") {}

void Test::setup()
{
    OgreBites::ApplicationContext::setup();
    root = OgreBites::ApplicationContext::getRoot();
    scnMgr = root->createSceneManager();

    shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    Ogre::RenderWindow* renderWid = getRenderWindow();
//    scnMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
//    scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Ogre::Camera* camera = scnMgr->createCamera("camera");
    renderWid->addViewport(camera);
    camera->setNearClipDistance(5);
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->attachObject(camera);
    camNode->setPosition(0, 0, 0);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_PARENT);
    camera->setFOVy(Ogre::Radian(3.14/1.75));
}

int main()
{
    Test test;
    test.initApp();
//    test.test();
    test.getRoot()->startRendering();
    test.closeApp();
    return 0;
}