#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include"PointCloud.h"
#include"PCNode.h"
#include"Splitter.h"
#include"OgreApplicationContext.h"
#include"Render.h"
#include"OgreOverlay.h"
#include"OgreOverlayManager.h"
#include"OgreOverlaySystem.h"
#include"OgreOverlayContainer.h"
#include"OgreRectangle2D.h"
#include"Ogre.h"

class Test : public OgreBites::ApplicationContext
{
private:
    Ogre::Root* root;
    Ogre::SceneManager* scnMgr;

    Ogre::RTShader::ShaderGenerator* shadergen;
    Ogre::RenderWindow* renderWid;
    std::vector<PCNode*> nodeList;

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

    Ogre::OverlaySystem* overlaySystem = OgreBites::ApplicationContext::getOverlaySystem();
    scnMgr->addRenderQueueListener(overlaySystem);

    shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    Ogre::RenderWindow* renderWindow = getRenderWindow();
    scnMgr->setAmbientLight(Ogre::ColourValue());
    PointCloud pc0("/home/spectre/CLionProjects/Minos/Pasha_guard_head400K.txt");
    // PointCloud pc0("/home/spectre/CLionProjects/Minos/test.txt");
    // PointCloud pc1("/home/spectre/CLionProjects/Minos/Centurion_helmet400K.txt");

    Ogre::SceneNode* node0 = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode* node1 = scnMgr->getRootSceneNode()->createChildSceneNode();
    node0->setScale(0.05, 0.05, 0.05);

    PCNode* pcnode0 = new PCNode(&pc0, node0);
    // PCNode* pcnode1 = new PCNode(&pc1, node1);
    nodeList.push_back(pcnode0);
    // nodeList.push_back(pcnode1);
    node0->setPosition(0, 0, -30);
    node0->rotate(Ogre::Vector3(-1, 0, 0), Ogre::Radian(Ogre::Degree(90)));
    // node1->setPosition(0, 0, 100);

    Ogre::Camera* camera = scnMgr->createCamera("camera");
    Ogre::Viewport* vp = renderWindow->addViewport(camera);
    camera->setNearClipDistance(5);
    std::cout << camera->getPlaneBoundedVolume().planes[0] << std::endl;
    std::cout << camera->getPlaneBoundedVolume().planes[1] << std::endl;
    std::cout << camera->getPlaneBoundedVolume().planes[2] << std::endl;
    std::cout << camera->getPlaneBoundedVolume().planes[3] << std::endl;
    std::cout << camera->getPlaneBoundedVolume().planes[4] << std::endl;
    std::cout << camera->getPlaneBoundedVolume().planes[5] << std::endl;

    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->attachObject(camera);
    camNode->setPosition(0, 0, 50);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
    camNode->translate(1, 0, 0);

    int height = vp->getActualHeight();
    int width = vp->getActualWidth();

    std::vector<RenderInfNode> renderList;

    int sub_cones = 2;
    Splitter splitter(camera, vp);
    splitter.split(sub_cones);
    Ogre::SceneNode* renderSNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Render render(scnMgr, renderSNode);

    for(int i = 0; i < sub_cones; ++i)
    {
        pcnode0->genRenderInf(splitter.getCombiner(i)->PBV, renderList);
        render.updateData(renderList);
        render.updateCamera(
            camera,
            splitter.getCombiner(i)->width,
            splitter.getCombiner(i)->height,
            splitter.getCombiner(i)->projMatrix
        );
        render.update(splitter.getCombiner(i)->pb);
        renderList.clear();
    }

    Ogre::PixelBox pb(width, height, 1, Ogre::PF_R8G8B8, new char[3 * width * height]);
    splitter.combine(pb);

    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
        "Tex", 
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
        Ogre::TEX_TYPE_2D, 
        vp->getActualWidth(),
        vp->getActualHeight(),
        0,
        Ogre::PF_R8G8B8,
        Ogre::TU_RENDERTARGET
    );
    texture->getBuffer(0, 0)->blitFromMemory(pb);

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
    material->getTechnique(0)->getPass(0)->createTextureUnitState("Tex");
    material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

    Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
    rect->setCorners(-1.0, 1.0, 1.0, -1.0);
    rect->setMaterial(material);
    rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    rect->setBoundingBox(aabInf);

    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(rect);

    renderSNode->setVisible(false);
}

int main()
{
    Test test;
    test.initApp();
    test.getRoot()->startRendering();
    test.closeApp();
    return 0;
}
