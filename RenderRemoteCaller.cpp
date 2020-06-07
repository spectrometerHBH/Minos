#include "RenderRemoteCaller.h"
#include "RenderInf.h"

#include <sockpp/tcp_connector.h>
#include <sockpp/version.h>

void RenderRemoteCaller::updateCamera(Ogre::Camera* camera, Ogre::SceneNode* camNode, int width, int height, Ogre::Matrix4 projMatrix)
{
  char *buffer = new char[1024], *start = buffer;
  buffer = RenderInfNode::serialize(buffer, 0);
  buffer = RenderInfNode::serialize(buffer, camera->getNearClipDistance());
  buffer = RenderInfNode::serialize(buffer, camNode->_getDerivedPosition());
  buffer = RenderInfNode::serialize(buffer, camera->getRealDirection());
  buffer = RenderInfNode::serialize(buffer, width);
  buffer = RenderInfNode::serialize(buffer, height);
  buffer = RenderInfNode::serialize(buffer, projMatrix);
  std::cout << "Camera " << size_t(buffer - start) << std::endl;
  std::cout << camera->getNearClipDistance() << std::endl;
  std::cout << camNode->_getDerivedPosition() << std::endl;
  std::cout << camera->getRealDirection() << std::endl;
  std::cout << width << " " << height << std::endl;
  std::cout << projMatrix << std::endl;
  sockpp::tcp_connector conn({"localhost", port});
  ssize_t len = conn.write_n(start, size_t(buffer - start));
  std::cout << len << std::endl;
}

void RenderRemoteCaller::updateData(const std::vector<RenderInfNode>& list)
{
  char *buffer = new char[70000000], *start = buffer;
  buffer = RenderInfNode::serialize(buffer, 1);
  buffer = RenderInfNode::serialize(buffer, int(list.size()));
  for (const auto& renderInfo : list)
    buffer = renderInfo.toBuffer(buffer);
  std::cout << "Data " << size_t(buffer - start) << " " << list[0].size << std::endl;
  sockpp::tcp_connector conn({"localhost", port});
  ssize_t len = conn.write_n(start, size_t(buffer - start));
  std::cout << len << std::endl;
}

void RenderRemoteCaller::update(const Ogre::PixelBox& pixelBox) {
  char* buffer = new char[1024], * start = buffer;
  buffer = RenderInfNode::serialize(buffer, 2);
  buffer = RenderInfNode::serialize(buffer, int(pixelBox.getWidth()));
  buffer = RenderInfNode::serialize(buffer, int(pixelBox.getHeight()));
  std::cout << "Update " << size_t(buffer - start) << " " << pixelBox.getWidth() << " "
            << pixelBox.getHeight() << std::endl;
  sockpp::tcp_connector conn({"localhost", port});
  ssize_t len = conn.write_n(start, size_t(buffer - start));
  conn.shutdown(SHUT_WR);
  std::cout << len << std::endl;

  char pixelBuffer[pixelBox.getConsecutiveSize()];
  len = conn.read_n(pixelBuffer, pixelBox.getConsecutiveSize());
  std::cout << pixelBox.getConsecutiveSize() << " " << len << std::endl;

  memcpy(pixelBox.data, pixelBuffer, pixelBox.getConsecutiveSize());
}
