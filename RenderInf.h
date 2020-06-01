#ifndef RENDERINF_H
#define RENDERINF_H

#include"Ogre.h"
#include<vector>

class RenderInfNode
{
public:
    int id;
    bool updateObject;
    std::vector<Ogre::Vector3> pos, color;
    Ogre::Vector3 nodePos, nodeScale;
    Ogre::Quaternion orientation;

    char* toBuffer(char* buffer);
    void fromBuffer(const char* buffer);
};

#endif