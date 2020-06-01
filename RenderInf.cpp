#include "RenderInf.h"

template<typename T>
char* serialize(char* buffer, T value) {
  memcpy(buffer, &value, sizeof(T));
  return buffer + sizeof(T);
}

char* serialize(char* buffer, Ogre::Vector3 value) {
  buffer = serialize(buffer, value.x);
  buffer = serialize(buffer, value.y);
  buffer = serialize(buffer, value.z);
  return buffer;
}

template<typename T>
char* serializeArray(char* buffer, T* array, int len) {
  for (int i = 0; i < len; ++i)
    buffer = serialize(buffer, array[i]);
  return buffer;
}

template<typename T>
const char* deserialize(const char* buffer, T& value) {
  memcpy(&value, buffer, sizeof(T));
  return const_cast<char*>(buffer + sizeof(T));
}

const char* deserialize(const char* buffer, Ogre::Vector3& value) {
  buffer = deserialize(buffer, value.x);
  buffer = deserialize(buffer, value.y);
  buffer = deserialize(buffer, value.z);
  return buffer;
}

template<typename T>
const char* deserializeArray(const char* buffer, T* array, int len) {
  for (int i = 0; i < len; ++i)
    buffer = deserialize(buffer, array[i]);
  return buffer;
}

char* RenderInfNode::toBuffer(char *buffer) {
  buffer = serialize(buffer, id);
  buffer = serialize(buffer, (int)updateObject);
  buffer = serialize(buffer, nodePos);
  buffer = serialize(buffer, nodeScale);
  buffer = serialize(buffer, pos.size());
  buffer = serializeArray(buffer, pos.data(), pos.size());
  buffer = serializeArray(buffer, color.data(), pos.size());
  return buffer;
}

void RenderInfNode::fromBuffer(const char* buffer) {
  buffer = deserialize(buffer, id);
  int upd = 0;
  buffer = deserialize(buffer, upd);
  this->updateObject = (bool)upd;
  buffer = deserialize(buffer, nodePos);
  buffer = deserialize(buffer, nodeScale);
  size_t len = 0;
  buffer = deserialize(buffer, len);
  auto* pos_ptr = new Ogre::Vector3[len];
  auto* color_ptr = new Ogre::Vector3[len];
  buffer = deserializeArray(buffer, pos_ptr, len);
  buffer = deserializeArray(buffer, color_ptr, len);
  this->pos.assign(pos_ptr, pos_ptr + len);
  this->color.assign(color_ptr, color_ptr + len);
}