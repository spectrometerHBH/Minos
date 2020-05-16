#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include"KDTree.h"
#include"Ogre.h"

class KDTree;

class PointCloud
{
public:
    std::vector<Ogre::Vector3> pos, color;

private:
    KDTree* kdTree;

public:
    PointCloud(const std::string&);
    ~PointCloud();

    bool fetchPoint(const Ogre::PlaneBoundedVolume*, std::vector<int>&);

private:
    void append(const std::string&);
};

#endif