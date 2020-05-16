#ifndef KDTREE_H
#define KDTREE_H

#include "PointCloud.h"

class PointCloud;

class KDTree
{
    class Node;

private:
    const PointCloud* pc;
    Node* root = NULL;

public:
    KDTree(const PointCloud*);
    ~KDTree();
    bool fetchPoint(const Ogre::PlaneBoundedVolume*, std::vector<int>&);

private:
    int sortIndex;

    void buildTree();
    KDTree::Node* buildTree(int, std::vector<int>&, int, int);
    bool cmp(int, int);
    int fetchPoint(Node*, const Ogre::PlaneBoundedVolume*, std::vector<int>&, bool);

private:
    class Node
    {
    public:
        Node* son[2];
        Ogre::AxisAlignedBox aabb;
        int index;
        int last = 0;
        int size;

    public:
        Node() = delete;
        Node(
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            Ogre::Real,
            int
        );
        ~Node();
    };
};

#endif