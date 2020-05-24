#include"KDTree.h"
#include<algorithm>
#include<iostream>

KDTree::KDTree(const PointCloud* pc) : pc(pc)
{
    buildTree();
}

KDTree::~KDTree()
{
    delete root;
}

KDTree::Node::Node(
    Ogre::Real mx, Ogre::Real my, Ogre::Real mz,
    Ogre::Real Mx, Ogre::Real My, Ogre::Real Mz,
    int index
) : aabb(mx, my, mz, Mx, My, Mz), index(index)
{
    son[0] = son[1] = NULL;
}

KDTree::Node::~Node()
{
    delete son[0];
    delete son[1];
}

void KDTree::buildTree()
{
    sortPc = pc;
    std::vector<int> tmp;
    for(int i = 0; i < pc->pos.size(); ++i)
        tmp.push_back(i);
    root = buildTree(0, tmp, 0, tmp.size() - 1);
}

KDTree::Node* KDTree::buildTree(int index, std::vector<int>& list, int l, int r)
{
    sortIndex = index;
    std::sort(list.begin() + l, list.begin() + r + 1, cmp);

    int mid = (l + r) / 2;
    Ogre::Real mx, my, mz, Mx, My, Mz;
    mx = Mx = pc->pos[l][0];
    my = My = pc->pos[l][1];
    mz = Mz = pc->pos[l][2];
    for(int i = l + 1; i <= r; ++i)
    {
        mx = std::min(mx, pc->pos[i][0]);
        Mx = std::max(Mx, pc->pos[i][0]);
        my = std::min(my, pc->pos[i][1]);
        My = std::max(My, pc->pos[i][1]);
        mz = std::min(mz, pc->pos[i][2]);
        Mz = std::max(Mz, pc->pos[i][2]);
    }
    Node* node = new Node(mx, my, mz, Mx, My, Mz, list[mid]);
    node->size = r - l + 1;
    if(mid > l)
        node->son[0] = buildTree((index + 1) % 3, list, l, mid - 1);
    if(mid < r)
        node->son[1] = buildTree((index + 1) % 3, list, mid + 1, r);
    return node;
}

bool KDTree::cmp(int l, int r)
{
    return sortPc->pos[l][sortIndex] < sortPc->pos[r][sortIndex];
}

bool KDTree::fetchPoint(const Ogre::PlaneBoundedVolume* plane, std::vector<int>& result)
{
    if(fetchPoint(root, plane, result, false))
    {
        fetchPoint(root, plane, result, true);
//        std::sort(result.begin(), result.end());
/*
        for(int i = 0; i < result.size(); ++i)
            if(i != result[i])
                std::cout << result[i] << std::endl;
*/
        return true;
    }
    return false;
}
int KDTree::fetchPoint(Node* now, const Ogre::PlaneBoundedVolume* plane, std::vector<int>& result, bool update)
{
    int len = plane->planes.size();
    int allSelected = true;

    for(int i = 0; i < len; ++i)
    {
        Ogre::Plane::Side test = plane->planes[i].getSide(now->aabb);
        if(test == Ogre::Plane::NEGATIVE_SIDE)
        {
            if(update)
            {
                now->last = 0;
                return 0;
            }
            else
                return now->last != 0;
        }

        if(test != Ogre::Plane::POSITIVE_SIDE)
            allSelected = false;
    }

    if(allSelected && !update)
        return now->last != now->size;

    int flag = true;
    int cnt = 0;
    for(int i = 0; i < len; ++i)
        if(plane->planes[i].getSide(pc->pos[now->index]) == Ogre::Plane::NEGATIVE_SIDE)
        {
            flag = false;
            break;
        }

    if(flag && update)
    {
        ++cnt;
//        if(std::rand() % 8 == 0)
            result.push_back(now->index);
    }

    if(now->son[0] != NULL)
        cnt += fetchPoint(now->son[0], plane, result, update);
    if(now->son[1] != NULL)
        cnt += fetchPoint(now->son[1], plane, result, update);
    if(update)
        now->last = cnt;

    return cnt;
}
/*
int KDTree::fetchPoint(Node* now, const Ogre::PlaneBoundedVolume* plane, std::vector<int>& result, bool update)
{
    if(!update)
        return 1;
    result.push_back(now->index);
    if(now->son[0] != NULL)
        fetchPoint(now->son[0], plane, result, update);
    if(now->son[1] != NULL)
        fetchPoint(now->son[1], plane, result, update);
    return 1;
}
*/