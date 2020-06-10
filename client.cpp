#include <iostream>
#include <string>
#include "RenderInf.h"
#include "OGRE/Ogre.h"
#include "RenderRemoteCaller.h"
#include "PointCloud.h"
#include "PCNode.h"
#include "Splitter.h"
#include "OgreApplicationContext.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreRectangle2D.h"

class Test : public OgreBites::ApplicationContext, public OgreBites::InputListener {
 private:
  Ogre::Root* root;
  Ogre::SceneManager* scnMgr;
  Ogre::Camera* camera;
  Ogre::SceneNode* camNode;
  Ogre::TexturePtr texture;
  Ogre::Viewport* vp;
  Ogre::RTShader::ShaderGenerator* shadergen;
  Ogre::RenderWindow* renderWindow;
  std::vector<PCNode*> nodeList;

 public:
  Test();
  void setup();
  void draw();
  void test();
  bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
};

Test::Test() : OgreBites::ApplicationContext("Ogre_Test") {}

bool Test::keyPressed(const OgreBites::KeyboardEvent& evt) {
  Ogre::Vector3 translate = Ogre::Vector3(0, 0, 0);
  Ogre::Real delta = 1;
  switch (evt.keysym.sym) {
    case OgreBites::SDLK_ESCAPE: {
      getRoot()->queueEndRendering();
      break;
    }
    case int('w'): {
      translate += Ogre::Vector3(0, delta, 0);
      break;
    }
    case int('s'): {
      translate += Ogre::Vector3(0, -delta, 0);
      break;
    }
    case int('a'): {
      translate += Ogre::Vector3(-delta, 0, 0);
      break;
    }
    case int('d'): {
      translate += Ogre::Vector3(delta, 0, 0);
      break;
    }
    default:
      return false;
  }

  camNode->translate(translate);
  std::cout << evt.keysym.sym << " " << translate << std::endl;

  draw();

  return true;
}

void Test::draw() {
  std::cout << "DRAWING.............................................." << std::endl;
  int height = vp->getActualHeight();
  int width = vp->getActualWidth();
  std::cout << height << " " << width << std::endl;
  std::vector<RenderInfNode> renderList;

  int sub_cones = 2;
  Splitter splitter(camera, vp);
  splitter.split(sub_cones);

  // set up tcp connection with render nodes
  std::vector<RenderRemoteCaller> renderCaller{RenderRemoteCaller(6666), RenderRemoteCaller(9999)};

  std::cout << "???" << std::endl;
  for (size_t i = 0; i < renderCaller.size(); ++i) {
    nodeList[0]->genRenderInf(splitter.getCombiner(i)->PBV, renderList);
    std::cout << renderList[0].id << std::endl;
    std::cout << renderList[0].updateObject << std::endl;
    std::cout << renderList[0].size << std::endl;
    std::cout << renderList[0].nodePos << std::endl;
    std::cout << renderList[0].nodeScale << std::endl;
    std::cout << renderList[0].orientation << std::endl;
    std::cout << renderList[0].data.get()[0] << " " << renderList[0].data.get()[1] << " "
              << renderList[0].data.get()[2] << " "
              << renderList[0].data.get()[3] << " " << renderList[0].data.get()[4] << "  "
              << renderList[0].data.get()[5] << std::endl;
    renderCaller[i].updateData(renderList);
    renderCaller[i].updateCamera(
        camera,
        camNode,
        splitter.getCombiner(i)->width,
        splitter.getCombiner(i)->height,
        splitter.getCombiner(i)->projMatrix
    );
    renderCaller[i].update(splitter.getCombiner(i)->pb);
    renderList.clear();
  }

  Ogre::PixelBox pb(width, height, 1, Ogre::PF_R8G8B8, new char[3 * width * height]);
  splitter.combine(pb);

  texture->setWidth(vp->getActualWidth());
  texture->setHeight(vp->getActualHeight());

  texture->getBuffer(0, 0)->blitFromMemory(pb);
}

void Test::setup() {
  OgreBites::ApplicationContext::setup();
  addInputListener(this);

  root = OgreBites::ApplicationContext::getRoot();
  scnMgr = root->createSceneManager();

  Ogre::OverlaySystem* overlaySystem = OgreBites::ApplicationContext::getOverlaySystem();
  scnMgr->addRenderQueueListener(overlaySystem);

  shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  renderWindow = getRenderWindow();
  scnMgr->setAmbientLight(Ogre::ColourValue());
  PointCloud* pc0 = new PointCloud("/home/spectre/CLionProjects/Minos/Pasha_guard_head400K.txt");
  // PointCloud pc0("/home/spectre/CLionProjects/Minos/test.txt");
  // PointCloud pc1("/home/spectre/CLionProjects/Minos/Centurion_helmet400K.txt");

  Ogre::SceneNode* node0 = scnMgr->getRootSceneNode()->createChildSceneNode();
  node0->setScale(0.05, 0.05, 0.05);
  node0->rotate(Ogre::Vector3(-1, 0, 0), Ogre::Radian(Ogre::Degree(90)));
  node0->setPosition(0, 0, -30);

  PCNode* pcnode0 = new PCNode(pc0, node0);
  nodeList.push_back(pcnode0);

  camera = scnMgr->createCamera("camera");
  vp = renderWindow->addViewport(camera);
  camera->setNearClipDistance(5);
  camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->attachObject(camera);
  camNode->setPosition(0, 0, 50);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
  camNode->translate(1, 0, 0);

  std::cout << camera->getPlaneBoundedVolume().planes[0] << std::endl;
  std::cout << camera->getPlaneBoundedVolume().planes[1] << std::endl;
  std::cout << camera->getPlaneBoundedVolume().planes[2] << std::endl;
  std::cout << camera->getPlaneBoundedVolume().planes[3] << std::endl;
  std::cout << camera->getPlaneBoundedVolume().planes[4] << std::endl;
  std::cout << camera->getPlaneBoundedVolume().planes[5] << std::endl;

  texture = Ogre::TextureManager::getSingleton().createManual(
      "Tex",
      Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
      Ogre::TEX_TYPE_2D,
      vp->getActualWidth(),
      vp->getActualHeight(),
      0,
      Ogre::PF_R8G8B8,
      Ogre::TU_RENDERTARGET
  );

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

  draw();
}

int main() {
  Test test;
  test.initApp();
  test.getRoot()->startRendering();
  test.closeApp();
  return 0;
}