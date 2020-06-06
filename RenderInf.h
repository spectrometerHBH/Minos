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

  char* toBuffer(char *buffer) const;
  void fromBuffer(const char* buffer);

  template<typename T>
  static char* serialize(char* buffer, T value);
  static char* serialize(char* buffer, Ogre::Vector3 value);
  static char* serialize(char* buffer, Ogre::Quaternion value);
  static char* serialize(char* buffer, Ogre::Matrix4 value);
  template<typename T>
  static char* serializeArray(char* buffer, std::shared_ptr<T> array, int len);

  template<typename T>
  static const char* deserialize(const char* buffer, T& value);
  static const char* deserialize(const char* buffer, Ogre::Vector3& value);
  template<typename T>
  static const char* deserializeArray(const char* buffer, std::shared_ptr<T> array, int len);
};

#endif