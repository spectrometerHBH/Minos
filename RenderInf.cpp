#include "RenderInf.h"

template<typename T>
char* RenderInfNode::serialize(char* buffer, T value) {
  memcpy(buffer, &value, sizeof(T));
  return buffer + sizeof(T);
}

char* RenderInfNode::serialize(char* buffer, size_t value) {
  memcpy(buffer, &value, sizeof(size_t));
  return buffer + sizeof(size_t);
}

char* RenderInfNode::serialize(char* buffer, Ogre::uint32 value) {
  memcpy(buffer, &value, sizeof(size_t));
  return buffer + sizeof(size_t);
}

char* RenderInfNode::serialize(char* buffer, Ogre::Vector3 value) {
  buffer = serialize(buffer, value.x);
  buffer = serialize(buffer, value.y);
  buffer = serialize(buffer, value.z);
  return buffer;
}

char* RenderInfNode::serialize(char* buffer, Ogre::Quaternion value) {
  buffer = serialize(buffer, value.w);
  buffer = serialize(buffer, value.x);
  buffer = serialize(buffer, value.y);
  buffer = serialize(buffer, value.z);
  return buffer;
}

char* RenderInfNode::serialize(char* buffer, Ogre::Matrix4 value) {
  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      buffer = serialize(buffer, value[i][j]);
  return buffer;
}

template<typename T>
char* RenderInfNode::serializeArray(char* buffer, std::shared_ptr<T> array, int len) {
  memcpy(buffer, array.get(), len * sizeof(T));
  return buffer + len * sizeof(T);
}

template<typename T>
const char* RenderInfNode::deserialize(const char* buffer, T& value) {
  memcpy(&value, buffer, sizeof(T));
  return const_cast<char*>(buffer + sizeof(T));
}

const char* RenderInfNode::deserialize(const char* buffer, size_t& value) {
  memcpy(&value, buffer, sizeof(size_t));
  return const_cast<char*>(buffer + sizeof(size_t));
}

const char* RenderInfNode::deserialize(const char* buffer, Ogre::uint32& value) {
  memcpy(&value, buffer, sizeof(uint32_t));
  return const_cast<char*>(buffer + sizeof(uint32_t));
}

const char* RenderInfNode::deserialize(const char* buffer, Ogre::Vector3& value) {
  buffer = deserialize(buffer, value.x);
  buffer = deserialize(buffer, value.y);
  buffer = deserialize(buffer, value.z);
  return buffer;
}

const char* RenderInfNode::deserialize(const char* buffer, Ogre::Quaternion& value) {
  buffer = deserialize(buffer, value.w);
  buffer = deserialize(buffer, value.x);
  buffer = deserialize(buffer, value.y);
  buffer = deserialize(buffer, value.z);
  return buffer;
}

const char* RenderInfNode::deserialize(const char* buffer, Ogre::Matrix4& value) {
  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 4; ++j)
      buffer = deserialize(buffer, value[i][j]);
  return buffer;
}

template<typename T>
const char* RenderInfNode::deserializeArray(const char* buffer, std::shared_ptr<T> array, int len) {
  memcpy(array.get(), buffer, len * sizeof(T));
  return buffer + len * sizeof(T);
}

char* RenderInfNode::toBuffer(char *buffer) const {
  buffer = serialize(buffer, id);
  buffer = serialize(buffer, (int)updateObject);
  buffer = serialize(buffer, size);
  buffer = serialize(buffer, nodePos);
  buffer = serialize(buffer, nodeScale);
  buffer = serializeArray(buffer, this->data, size);
  return buffer;
}

void RenderInfNode::fromBuffer(const char* buffer) {
  int upd = 0;
  buffer = deserialize(buffer, this->id);
  buffer = deserialize(buffer, upd);
  buffer = deserialize(buffer, this->size);
  buffer = deserialize(buffer, this->nodePos);
  buffer = deserialize(buffer, this->nodeScale);
  auto* data_ptr = new float[size];
  this->data.reset(data_ptr);
  buffer = deserializeArray(buffer, this->data, size);
  this->updateObject = (bool)upd;
}
