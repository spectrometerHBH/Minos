#ifndef PCNODE_H
#define PCNODE_H

#include"Ogre.h"
#include"PointCloud.h"
#include"RenderInf.h"

class PCNode
{
private:
    inline static int _count = 0;

    int id;
    PointCloud* pc;
    Ogre::SceneNode* scnNode;

public:
    PCNode(PointCloud*, Ogre::SceneNode*);
    void genRenderInf(const Ogre::PlaneBoundedVolume&, std::vector<RenderInfNode>&);

private:
    int fetchPoint(const Ogre::PlaneBoundedVolume&, std::shared_ptr<float> &);
};

#endif