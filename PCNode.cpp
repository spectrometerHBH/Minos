#include"PCNode.h"
#include<algorithm>

PCNode::PCNode(PointCloud* pc, Ogre::SceneNode* scnNode) : pc(pc), scnNode(scnNode), id(_count++) {}

int PCNode::fetchPoint(const Ogre::PlaneBoundedVolume& _plane, std::shared_ptr<float> &result)
{
    Ogre::PlaneBoundedVolume plane = _plane;
    int len = plane.planes.size();
    for(int i = 0; i < len; ++i)
    {
        Ogre::Vector3 origin = - plane.planes[i].d * plane.planes[i].normal;
        plane.planes[i].normal = scnNode->convertWorldToLocalDirection(plane.planes[i].normal, false);
        origin = -scnNode->convertWorldToLocalPosition(origin);
        plane.planes[i].d = origin.dotProduct(plane.planes[i].normal);
    }
    return pc->fetchPoint(&plane, result);
}

void PCNode::genRenderInf(const Ogre::PlaneBoundedVolume& plane, std::vector<RenderInfNode>& renderInf)
{
    RenderInfNode renderInfNode;
    renderInfNode.id = id;
    std::shared_ptr<float> data;
    renderInfNode.size = fetchPoint(plane, data);
    renderInfNode.updateObject = renderInfNode.size != -1;
    renderInfNode.data = data;
    renderInfNode.nodePos = scnNode->convertLocalToWorldPosition(Ogre::Vector3(0, 0, 0));
    renderInfNode.nodeScale = scnNode->getScale();
    renderInfNode.orientation = scnNode->getOrientation();
    renderInf.push_back(renderInfNode);
}