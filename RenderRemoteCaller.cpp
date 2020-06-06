#include "RenderRemoteCaller.h"
#include "RenderInf.h"

void RenderRemoteCaller::updateCamera(Ogre::Camera* camera, Ogre::SceneNode* camNode, int width, int height, Ogre::Matrix4 projMatrix)
{
  auto enterCallback = [=](const TcpConnection::Ptr& session) {
    char *buffer = new char[1024], *start = buffer;
    buffer = RenderInfNode::serialize(buffer, 0);
    buffer = RenderInfNode::serialize(buffer, camera->getNearClipDistance());
    buffer = RenderInfNode::serialize(buffer, camNode->_getDerivedPosition());
    buffer = RenderInfNode::serialize(buffer, camNode->_getDerivedOrientation());
    buffer = RenderInfNode::serialize(buffer, width);
    buffer = RenderInfNode::serialize(buffer, height);
    buffer = RenderInfNode::serialize(buffer, projMatrix);
    std::cout << "Camera " << size_t(buffer - start) << std::endl;
    session->send(start, buffer - start);
  };
  connectionBuilder.configureConnectionOptions({
    brynet::net::AddSocketOption::AddEnterCallback(enterCallback),
    brynet::net::AddSocketOption::WithMaxRecvBufferSize(1024)
  });
  connectionBuilder.configureConnectOptions({
    ConnectOption::WithAddr("localhost", port),
    ConnectOption::WithTimeout(std::chrono::seconds(10)),
    ConnectOption::AddProcessTcpSocketCallback([](TcpSocket& socket) { socket.setNodelay(); })
  }).syncConnect();
}

void RenderRemoteCaller::updateData(const std::vector<RenderInfNode>& list)
{
  auto enterCallback = [&](const TcpConnection::Ptr& session) {
    char *buffer = new char[70000000], *start = buffer;
    buffer = RenderInfNode::serialize(buffer, 1);
    buffer = RenderInfNode::serialize(buffer, int(list.size()));
    for (const auto& renderInfo : list)
      buffer = renderInfo.toBuffer(buffer);
    std::cout << "Data " << size_t(buffer - start) << " " << list[0].size << std::endl;
    session->send(start, buffer - start);
  };
  connectionBuilder.configureConnectionOptions({
    brynet::net::AddSocketOption::AddEnterCallback(enterCallback),
    brynet::net::AddSocketOption::WithMaxRecvBufferSize(70000000)
  });
  connectionBuilder.configureConnectOptions({
    ConnectOption::WithAddr("localhost", port),
    ConnectOption::WithTimeout(std::chrono::seconds(10)),
    ConnectOption::AddProcessTcpSocketCallback([](TcpSocket& socket) { socket.setNodelay(); })
  }).syncConnect();
}


void RenderRemoteCaller::update(const Ogre::PixelBox& pixelBox)
{
  auto enterCallback = [&](const TcpConnection::Ptr& session) {
    session->setDataCallback([session, &pixelBox](const char* buffer, size_t len) {
      memcpy(pixelBox.data, buffer, len);
      return len;
    });
    char *buffer = new char[1024], *start = buffer;
    buffer = RenderInfNode::serialize(buffer, 2);
    std::cout << "Update " << int(buffer - start) << std::endl;
    session->send(start, buffer - start);
  };
  connectionBuilder.configureConnectionOptions({
    brynet::net::AddSocketOption::AddEnterCallback(enterCallback),
    brynet::net::AddSocketOption::WithMaxRecvBufferSize(1024)
  });
  connectionBuilder.configureConnectOptions({
    ConnectOption::WithAddr("localhost", port),
    ConnectOption::WithTimeout(std::chrono::seconds(10)),
    ConnectOption::AddProcessTcpSocketCallback([](TcpSocket& socket) { socket.setNodelay(); })
  }).syncConnect();
}
