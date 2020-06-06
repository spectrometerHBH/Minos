#ifndef MINOS__RENDERREMOTECALLER_H_
#define MINOS__RENDERREMOTECALLER_H_

#include <iostream>
#include <map>
#include <vector>
#include "Ogre.h"
#include "RenderInf.h"

#include <brynet/net/SocketLibFunction.hpp>
#include <brynet/net/TcpService.hpp>
#include <brynet/net/AsyncConnector.hpp>
#include <brynet/net/wrapper/ConnectionBuilder.hpp>

using namespace brynet;
using namespace brynet::net;

class RenderRemoteCaller {
 public:
  RenderRemoteCaller(int port_) : port(port_) {
    auto service = TcpService::Create();
    service->startWorkerThread(1);
    auto connector = AsyncConnector::Create();
    connector->startWorkerThread();
    connectionBuilder.configureService(service).configureConnector(connector);
  }

  int port;
  wrapper::ConnectionBuilder connectionBuilder;

  void updateCamera(Ogre::Camera*, Ogre::SceneNode*, int, int, Ogre::Matrix4);
  void updateData(const std::vector<RenderInfNode>&);
  void update(const Ogre::PixelBox&);
};

#endif //MINOS__RENDERREMOTECALLER_H_
