#ifndef RENDER_H
#define RENDER_H

#include<map>
#include<vector>
#include"Ogre.h"
#include"RenderInf.h"

class Render
{
private:
    std::map<int, Ogre::SceneNode*> nodeList;
    std::map<int, Ogre::MeshPtr> meshList;
    Ogre::SceneManager* scnMgr;
    Ogre::SceneNode* root;
    Ogre::Camera* camera;
    Ogre::TexturePtr texture = NULL;
    Ogre::RenderTexture* rtt;
    inline static int universalIndex[800000];

public:
    Render(Ogre::SceneManager*, Ogre::SceneNode*);
    void updateCamera(Ogre::Camera*, int, int, Ogre::Matrix4);
    void updateData(const std::vector<RenderInfNode>&);
    void update(const Ogre::PixelBox&);
    ~Render();

private:
    void updateData(const RenderInfNode&);
};

#endif