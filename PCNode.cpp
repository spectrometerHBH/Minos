#include"PCNode.h"
#include<algorithm>

PCNode::PCNode(PointCloud* pc, Ogre::SceneNode* scnNode) : pc(pc), scnNode(scnNode), id(_count++) {}

bool PCNode::fetchPoint(const Ogre::PlaneBoundedVolume& _plane, std::vector<int>& result)
{
    Ogre::PlaneBoundedVolume plane = _plane;
    int len = plane.planes.size();
    for(int i = 0; i < len; ++i)
    {
        Ogre::Vector3 origin = - plane.planes[i].d * plane.planes[i].normal;
        plane.planes[i].normal = scnNode->convertWorldToLocalDirection(plane.planes[i].normal, false);
        origin = scnNode->convertWorldToLocalPosition(origin);
        plane.planes[i].d = origin.length();
    }
    return pc->fetchPoint(&plane, result);
}

void PCNode::genRenderInf(const Ogre::PlaneBoundedVolume& plane, std::vector<RenderInfNode>& renderInf)
{
    RenderInfNode renderInfNode;
    renderInfNode.id = id;
    std::vector<int> indexList;
    renderInfNode.updateObject = fetchPoint(plane, indexList);
    int len = indexList.size();

    if(renderInfNode.updateObject)
    {
        for(int i = 0; i < len; ++i)
        {
            renderInfNode.pos.push_back(pc->pos[indexList[i]]);
            renderInfNode.color.push_back(pc->color[indexList[i]]);
        }
    }
    renderInfNode.nodePos = scnNode->convertLocalToWorldPosition(Ogre::Vector3(0, 0, 0));
    renderInfNode.nodeScale = scnNode->getScale();
    renderInfNode.orientation = scnNode->getOrientation();
    renderInf.push_back(renderInfNode);
}