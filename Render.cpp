#include"Render.h"

Render::Render(Ogre::SceneNode* root, Ogre::Camera* camera, int width, int height) : root(root), camera(camera)
{
    Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(
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
        meshList.insert(std::make_pair(info.id, p));
    }

    Ogre::SceneNode* node = nodeList[info.id];
    Ogre::MeshPtr mesh = meshList[info.id];

    node->setScale(info.nodeScale);
    node->setPosition(info.nodePos);
    node->setOrientation(info.orientation);

    if(info.updateObject)
    {
        mesh->unload();
        int num = mesh->getNumSubMeshes();
        for(int i = num - 1; i >= 0; --i)
            mesh->destroySubMesh(i);
        
        if(!info.pos.empty())
        {
            Ogre::SubMesh* subMesh = mesh->createSubMesh();
            subMesh->operationType = Ogre::RenderOperation::OT_POINT_LIST;
            subMesh->vertexData = new Ogre::VertexData();
            subMesh->vertexData->vertexCount = info.pos.size();
            Ogre::VertexDeclaration* decl = subMesh->vertexData->vertexDeclaration;
            Ogre::VertexBufferBinding* bind = subMesh->vertexData->vertexBufferBinding;
            size_t offset = 0;
            offset += decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION).getSize();
            offset += decl->addElement(0, offset, Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE).getSize();
            Ogre::HardwareVertexBufferSharedPtr vbuf =
                Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                    offset, info.pos.size(), Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY
                );
            auto* vertices = new float[7 * info.pos.size()];
            for(int i = 0; i < info.pos.size(); ++i)
            {
                vertices[i + 0] = info.pos[i][0];
                vertices[i + 1] = info.pos[i][1];
                vertices[i + 2] = info.pos[i][2];
                vertices[i + 3] = info.color[i][0];
                vertices[i + 4] = info.color[i][1];
                vertices[i + 5] = info.color[i][3];
                vertices[i + 6] = 1;
            }
            vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
            bind->setBinding(0, vbuf);
            delete[] vertices;
        }
        mesh->load();
    }
}

void Render::update(Ogre::PixelBox& pixelBox)
{
    rtt->update();
    rtt->copyContentsToMemory(pixelBox);
}