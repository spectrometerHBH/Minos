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
    Ogre::SceneNode* root;
    Ogre::Camera* camera;
    Ogre::RenderTexture* rtt;

public:
    Render(Ogre::SceneNode*, Ogre::Camera*, int, int);
    void updateData(const std::vector<RenderInfNode>&);
    void update(Ogre::PixelBox&);

private:
    void updateData(const RenderInfNode&);
};

#endif