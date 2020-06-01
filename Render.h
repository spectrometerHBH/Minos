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
    Ogre::RenderTexture* rtt;
    inline static int universalIndex[800000];

public:
    Render(Ogre::SceneManager*, Ogre::SceneNode*, Ogre::Camera*, int, int);
    void updateData(const std::vector<RenderInfNode>&);
    void update(Ogre::PixelBox&);
    ~Render();

private:
    void updateData(const RenderInfNode&);
};

#endif