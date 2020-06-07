#include"Render.h"
#include<iostream>

Render::Render(Ogre::SceneManager* scnMgr, Ogre::SceneNode* root) : root(root), scnMgr(scnMgr)
{
  int size = sizeof(universalIndex) / sizeof(universalIndex[0]);
  for(int i = 0; i < size; ++i)
    universalIndex[i] = i;
}

void Render::updateCamera(Ogre::Camera* camera, int width, int height, Ogre::Matrix4 projMatrix)
{
  if(texture.getPointer() != NULL)
    Ogre::TextureManager::getSingleton().remove(texture);
  this->camera = camera;
  std::cout << camera->getName() << std::endl;
  texture = Ogre::TextureManager::getSingleton().createManual(
      camera->getName(),
      Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
      Ogre::TEX_TYPE_2D,
      width, height, 0,
      Ogre::PF_R8G8B8,
      Ogre::TU_RENDERTARGET
  );
  rtt = texture->getBuffer()->getRenderTarget();
  Ogre::Viewport* v = rtt->addViewport(camera);
  v->setBackgroundColour(Ogre::ColourValue::Black);
  camera->setCustomProjectionMatrix(true, projMatrix);
}

void Render::updateData(const std::vector<RenderInfNode>& list)
{
  int len = list.size();
  for(int i = 0; i < len; ++i)
    updateData(list[i]);
}

void Render::updateData(const RenderInfNode& info)
{
  if(nodeList.count(info.id) == 0)
  {
    nodeList.insert(std::make_pair(info.id, root->createChildSceneNode()));
    Ogre::MeshPtr p = Ogre::MeshManager::getSingleton().createManual(Ogre::StringConverter::toString(info.id), Ogre::RGN_DEFAULT);

    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    p->_setBounds(aabInf);

    meshList.insert(std::make_pair(info.id, p));
  }

  Ogre::SceneNode* node = nodeList[info.id];
  Ogre::MeshPtr mesh = meshList[info.id];

  node->setScale(info.nodeScale);
  node->setPosition(info.nodePos);
  node->setOrientation(info.orientation);

  if(info.updateObject && info.data != NULL)
  {
    node->detachAllObjects();
    mesh->unload();
    int num = mesh->getNumSubMeshes();
    for(int i = num - 1; i >= 0; --i)
      mesh->destroySubMesh(i);

    int size = info.size;
    std::cout << size << std::endl;
    if(size > 0)
    {
      Ogre::SubMesh* subMesh = mesh->createSubMesh();
      subMesh->useSharedVertices = false;
      subMesh->operationType = Ogre::RenderOperation::OT_POINT_LIST;
      subMesh->vertexData = new Ogre::VertexData();
      subMesh->vertexData->vertexCount = size;
      Ogre::VertexDeclaration* decl = subMesh->vertexData->vertexDeclaration;
      Ogre::VertexBufferBinding* bind = subMesh->vertexData->vertexBufferBinding;
      size_t offset = 0;
      offset += decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION).getSize();
      offset += decl->addElement(0, offset, Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE).getSize();
      Ogre::HardwareVertexBufferSharedPtr vbuf =
          Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
              offset, size, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY
          );
      vbuf->writeData(0, vbuf->getSizeInBytes(), info.data.get(), true);
      bind->setBinding(0, vbuf);

      Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
          Ogre::HardwareIndexBuffer::IT_32BIT,
          size,
          Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY
      );
      ibuf->writeData(0, ibuf->getSizeInBytes(), universalIndex, true);
      subMesh->indexData->indexBuffer = ibuf;
      subMesh->indexData->indexCount = size;
      subMesh->indexData->indexStart = 0;
      subMesh->setMaterialName("mat");
    }

    mesh->load();
    node->attachObject(scnMgr->createEntity(mesh));
  }
}

void Render::update(const Ogre::PixelBox& pixelBox)
{
  rtt->update();
  rtt->copyContentsToMemory(pixelBox);
}

Render::~Render()
{
}