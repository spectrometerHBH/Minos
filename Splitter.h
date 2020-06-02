#ifndef SPLITTER_H
#define SPLITTER_H

#include"Ogre.h"

class Combiner
{
public:
    int width, height;
    Ogre::Camera* camera;
    Ogre::Matrix4 projMatrix;
    Ogre::PixelBox pb;
    Ogre::PlaneBoundedVolume PBV;

    Combiner(int, int, Ogre::Camera*);
    ~Combiner();
};

class Splitter
{
private:
    Combiner **combiner = NULL;

    Ogre::Camera *camera;
    Ogre::Viewport *vp;
    int numOfCombiner = 0;

public:
    Splitter(Ogre::Camera*, Ogre::Viewport*);
    void split(int);
    const Combiner* getCombiner(int);
    void combine(Ogre::PixelBox &);
    ~Splitter();

private:
    void splitH(double, double, Combiner* &);
};

#endif