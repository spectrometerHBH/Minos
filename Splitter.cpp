#include"Splitter.h"
#include<iostream>

Combiner::Combiner(int height, int width, Ogre::Camera* camera) : 
height(height), width(width), camera(camera),
pb(width, height, 1, Ogre::PF_R8G8B8, new char[3 * width * height])
{
    PBV = camera->getPlaneBoundedVolume();
    projMatrix = camera->getProjectionMatrix();
}

Combiner::~Combiner()
{
    delete[] pb.data;
}

Splitter::Splitter(Ogre::Camera* camera, Ogre::Viewport* vp) : camera(camera), vp(vp) {}

Splitter::~Splitter()
{
    for(int i = 0; i < numOfCombiner; ++i)
        delete combiner[i];
    delete[] combiner;
}

void Splitter::split(int numOfRender)
{
    for(int i = 0; i < numOfCombiner; ++i)
        delete combiner[i];
    delete[] combiner;
    combiner = new Combiner*[numOfRender];
    numOfCombiner = numOfRender;

    double duration = 1.0 / numOfRender;
    double last = 0;
    for(int i = 0; i < numOfRender - 1; ++i, last += duration)
        splitH(last, last + duration, combiner[i]);
    splitH(last, 1, combiner[numOfRender - 1]);
}

void Splitter::splitH(double begin, double end, Combiner* &combiner)
{
    int height = vp->getActualHeight();
    int width = vp->getActualWidth();
    double ratio = end - begin;
    if(end == 1)
        width = width - width * begin;
    else
        width *= ratio;

    combiner = new Combiner(height, width, camera);
    Ogre::Real n = camera->getNearClipDistance();
    Ogre::Real r = n / combiner->projMatrix[0][0] * (combiner->projMatrix[0][2] + 1);
    Ogre::Real l = n / combiner->projMatrix[0][0] * (combiner->projMatrix[0][2] - 1);

    Ogre::Real _r = l + (r - l) * end;
    Ogre::Real _l = l + (r - l) * begin;
    combiner->projMatrix[0][0] = n * 2 / (_r - _l);
    combiner->projMatrix[0][2] = (_r + _l) / (_r - _l);

    Ogre::SceneNode* camNode = camera->getParentSceneNode();
    Ogre::Vector4 vec4(-1, 0, 0, 1);
    Ogre::Vector3 vec3;
    vec4 = combiner->projMatrix.transpose() * vec4;
    vec3 = camNode->convertLocalToWorldDirection(vec4.xyz(), false);
    vec3.normalise();
    combiner->PBV.planes[5] = Ogre::Plane(vec3, vec3.dotProduct(camNode->getPosition()));

    vec4 = Ogre::Vector4(1, 0, 0, 1);
    vec4 = combiner->projMatrix.transpose() * vec4;
    vec3 = camNode->convertLocalToWorldDirection(vec4.xyz(), false);
    vec3.normalise();
    combiner->PBV.planes[4] = Ogre::Plane(vec3, vec3.dotProduct(camNode->getPosition()));
}

void Splitter::combine(Ogre::PixelBox &pb)
{
    Ogre::uchar* data = pb.data;
    /*
    int height = vp->getActualHeight();
    for(int i = 0; i < 1; ++i)
    {
        int width = combiner[i]->width;
        memcpy(data, combiner[i]->pb.data, height * width * 3);
        data += height * width * 3;
    }
    */

    int height = vp->getActualHeight();
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < numOfCombiner; ++j)
        {
            memcpy(data, combiner[j]->pb.data + i * 3 * combiner[j]->width, 3 * combiner[j]->width);
            data += 3 * combiner[j]->width;
        }
    }
}

const Combiner* Splitter::getCombiner(int i)
{
    return combiner[i];
}