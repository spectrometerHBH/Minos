#include"Render.h"
#include<iostream>

Render::Render(Ogre::SceneManager* scnMgr, Ogre::SceneNode* root, Ogre::Camera* camera, int width, int height) : root(root), camera(camera)
{
    this->scnMgr = scnMgr;
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

    if(info.updateObject)
    {
        node->detachAllObjects();
        mesh->unload();
        int num = mesh->getNumSubMeshes();
        for(int i = num - 1; i >= 0; --i)
            mesh->destroySubMesh(i);
        
        if(info.pos.size() > 0)
        {
            Ogre::SubMesh* subMesh = mesh->createSubMesh();
            subMesh->useSharedVertices = false;
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
            float* vertices = new float[7 * info.pos.size()];
            for(int i = 0; i < info.pos.size(); ++i)
            {
                int base = i * 7;
                vertices[base + 0] = info.pos[i][0];
                vertices[base + 1] = info.pos[i][1];
                vertices[base + 2] = info.pos[i][2];
                vertices[base + 3] = info.color[i][0] / 255.0;
                vertices[base + 4] = info.color[i][1] / 255.0;
                vertices[base + 5] = info.color[i][2] / 255.0;
                vertices[base + 6] = 1;
            }
            vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
            bind->setBinding(0, vbuf);
            delete[] vertices;

            int* index = new int[info.pos.size()];
            for(int i = 0; i < info.pos.size(); ++i)
                index[i] = i;
            Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
                Ogre::HardwareIndexBuffer::IT_32BIT,
                info.pos.size(),
                Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY
            );
            ibuf->writeData(0, ibuf->getSizeInBytes(), index, true);
            subMesh->indexData->indexBuffer = ibuf;
            subMesh->indexData->indexCount = info.pos.size();
            subMesh->indexData->indexStart = 0;
            delete[] index;
        }

        mesh->load();
        node->attachObject(scnMgr->createEntity(mesh));
    }
}

void Render::update(Ogre::PixelBox& pixelBox)
{
    rtt->update();
    rtt->copyContentsToMemory(pixelBox);
}

Render::~Render()
{
}