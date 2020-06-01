#ifndef KDTREE_H
#define KDTREE_H

#include"Ogre.h"
#include"PointCloud.h"

class PointCloud;

class KDTree
{
    class Node;

private:
    const PointCloud* pc;
    Node* root = NULL;
    float* data;

public:
    KDTree(const PointCloud*);
    ~KDTree();
    int fetchPoint(const Ogre::PlaneBoundedVolume*, std::shared_ptr<float> &);

private:
    inline static int sortIndex;
    inline static const PointCloud* sortPc;
    bool updateModel;

    void buildTree();
    KDTree::Node* buildTree(int, std::vector<int>&, int, int);
    static bool cmp(int, int);
    int fetchPoint(Node*, const Ogre::PlaneBoundedVolume*, std::shared_ptr<float> &, bool, int&);

private:
    class Node
    {
    public:
        Node* son[2];
        Ogre::AxisAlignedBox aabb;
        int left, right, size;
        int last = 0;

    public:
        Node() = delete;
        Node(
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            int,
            int
        );
        ~Node();
    };
};

#endif