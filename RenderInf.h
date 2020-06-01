#ifndef RENDERINF_H
#define RENDERINF_H

#include"Ogre.h"
#include<vector>

class RenderInfNode
{
public:
    int id;
    int size;
    bool updateObject;
    std::shared_ptr<float> data = NULL;
    Ogre::Vector3 nodePos, nodeScale;
    Ogre::Quaternion orientation;

    char* toBuffer(char* buffer);
    void fromBuffer(const char* buffer);
};

#endif