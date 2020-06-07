#ifndef MINOS__RENDERREMOTECALLER_H_
#define MINOS__RENDERREMOTECALLER_H_

#include <iostream>
#include <map>
#include <vector>
#include "Ogre.h"
#include "RenderInf.h"

#include "sockpp/tcp_connector.h"
#include "sockpp/version.h"

class RenderRemoteCaller {
 public:
  RenderRemoteCaller(in_port_t port_) : port(port_) {}

  in_port_t port;

  void updateCamera(Ogre::Camera*, Ogre::SceneNode*, int, int, Ogre::Matrix4);
  void updateData(const std::vector<RenderInfNode>&);
  void update(const Ogre::PixelBox&);
};

#endif //MINOS__RENDERREMOTECALLER_H_
