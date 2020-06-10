#include <iostream>
#include <string>
#include "OGRE/Ogre.h"
#include "PCNode.h"
#include "OgreApplicationContext.h"
#include "OgreOverlay.h"
#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"
#include "OgreOverlayContainer.h"
#include "OgreRectangle2D.h"
#include "Render.h"
#include <sockpp/tcp_acceptor.h>

class Test : public OgreBites::ApplicationContext {
 private:
  Ogre::Root* root;
  Ogre::SceneManager* scnMgr;

  Ogre::RTShader::ShaderGenerator* shadergen;
  Ogre::RenderWindow* renderWid;
  std::vector<PCNode*> nodeList;

 public:
  in_port_t port;

  Test();
  void setup();
  void test();
};

Test::Test() : OgreBites::ApplicationContext("Ogre_Test") {}

void Test::setup() {
  OgreBites::ApplicationContext::setup();
  root = OgreBites::ApplicationContext::getRoot();
  scnMgr = root->createSceneManager();

  Ogre::OverlaySystem* overlaySystem = OgreBites::ApplicationContext::getOverlaySystem();
  scnMgr->addRenderQueueListener(overlaySystem);

  shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(scnMgr);

  Ogre::RenderWindow* renderWindow = getRenderWindow();
  scnMgr->setAmbientLight(Ogre::ColourValue());

  Ogre::Camera* camera = scnMgr->createCamera("camera");
  Ogre::Viewport* vp = renderWindow->addViewport(camera);
  Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->attachObject(camera);
  camNode->setPosition(0, 0, 50);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

  Ogre::SceneNode* renderSNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  Render render(scnMgr, renderSNode);

  sockpp::socket_initializer sockInit;
  sockpp::tcp_acceptor acc(port);

  if (!acc) {
    std::cout << "Error creating the acceptor: " << acc.last_error_str() << std::endl;
    exit(1);
  }
  std::cout << "Awaiting connections on port " << port << "..." << std::endl;

  while (true) {
    sockpp::inet_address peer;

    // Accept a new client connection
    sockpp::tcp_socket sock = acc.accept(&peer);
    std::cout << "Received a connection request from " << peer << std::endl;

    if (!sock) {
      std::cout << "Error accepting incoming connection: " << acc.last_error_str() << std::endl;
      exit(1);
    } else {
      ssize_t len;
      static char buffer[20000000];
      const char* packet = buffer;

      while ((len = sock.read_n(buffer, sizeof(buffer))) > 0)
        std::cout << len << std::endl;

      int command;
      packet = RenderInfNode::deserialize(packet, command);
      if (command == 0) {
        Ogre::Real nearClipDistance;
        Ogre::Vector3 position, direction;
        Ogre::Quaternion orientation;
        int width, height;
        Ogre::Matrix4 projMatrix;
        packet = RenderInfNode::deserialize(packet, nearClipDistance);
        packet = RenderInfNode::deserialize(packet, position);
        packet = RenderInfNode::deserialize(packet, orientation);
        packet = RenderInfNode::deserialize(packet, direction);
        packet = RenderInfNode::deserialize(packet, width);
        packet = RenderInfNode::deserialize(packet, height);
        packet = RenderInfNode::deserialize(packet, projMatrix);
        std::cout << nearClipDistance << std::endl;
        std::cout << position << std::endl;
        std::cout << orientation << std::endl;
        std::cout << direction << std::endl;
        std::cout << width << " " << height << std::endl;
        std::cout << projMatrix << std::endl;
        camera->setNearClipDistance(nearClipDistance);
        camNode->setPosition(position);
        camNode->lookAt(direction, Ogre::Node::TS_PARENT);
        camNode->setOrientation(orientation);

        render.updateCamera(camera, width, height, projMatrix);
      } else if (command == 1) {
        int size = 0;
        packet = RenderInfNode::deserialize(packet, size);
        std::vector<RenderInfNode> list;
        for (size_t i = 0; i < size; ++i) {
          RenderInfNode renderInfNode;
          renderInfNode.fromBuffer(packet);
          list.push_back(renderInfNode);
        }
        std::cout << list[0].id << std::endl;
        std::cout << list[0].updateObject << std::endl;
        std::cout << list[0].size << std::endl;
        std::cout << list[0].nodePos << std::endl;
        std::cout << list[0].nodeScale << std::endl;
        std::cout << list[0].data.get()[0] << " " << list[0].data.get()[1] << " " << list[0].data.get()[2] << " "
        << list[0].data.get()[3] << " " << list[0].data.get()[4] << "  " << list[0].data.get()[5] << "  " << list[0].data.get()[6] << std::endl;
        render.updateData(list);
      } else if (command == 2) {
        int width, height;
        packet = RenderInfNode::deserialize(packet, width);
        packet = RenderInfNode::deserialize(packet, height);
        std::cout << width << " " << height << std::endl;

        Ogre::PixelBox pb(width, height, 1, Ogre::PF_R8G8B8, new char[3 * width * height]);
        render.update(pb);

        std::cout << pb.getConsecutiveSize() << " " << std::endl;
        ssize_t len = sock.write_n(pb.data, pb.getConsecutiveSize());
        std::cout << len << std::endl;
        sock.shutdown(SHUT_WR);
      }
      std::cout << "Connection closed from " << sock.peer_address() << std::endl;
    }
  }
}

int main(int argc, char** argv) {
  Test test;
  if (argc != 2) {
    fprintf(stderr, "Usage: <listen port>\n");
    exit(-1);
  }
  test.port = atoi(argv[1]);
  test.initApp();
  test.getRoot()->startRendering();
  test.closeApp();
  return 0;
}