#include"PointCloud.h"

PointCloud::PointCloud(const std::string& file)
{
    append(file);
    kdTree = new KDTree(this);
}

PointCloud::~PointCloud()
{
    delete kdTree;
}

void PointCloud::append(const std::string& file)
{
    std::ifstream fin(file, std::ios::in);
    std::string line;
    int num;

    while(std::getline(fin, line))
    {
        if((line[0] < '0' || line[0] > '9') && line[0] != '-')
            continue;
        std::stringstream sin(line);
        sin >> num;
        break;
    }

    while(std::getline(fin, line))
    {
        if((line[0] < '0' || line[0] > '9') && line[0] != '-')
            continue;
        std::stringstream sin(line);
        double x, y, z, r, g, b;
        sin >> x >> y >> z >> r >> g >> b;
        pos.push_back(Ogre::Vector3(x, y, z));
        color.push_back(Ogre::Vector3(r, g, b));
    }
}

int PointCloud::fetchPoint(const Ogre::PlaneBoundedVolume* plane, std::shared_ptr<float> & result)
{
    return kdTree->fetchPoint(plane, result);
}