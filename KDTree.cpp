#include"KDTree.h"
#include<algorithm>
#include<iostream>

KDTree::KDTree(const PointCloud* pc) : pc(pc)
{
    buildTree();
}

KDTree::~KDTree()
{
    delete[] data;
    delete root;
}

KDTree::Node::Node(
    Ogre::Real mx, Ogre::Real my, Ogre::Real mz,
    Ogre::Real Mx, Ogre::Real My, Ogre::Real Mz,
    int left, int right
) : aabb(mx, my, mz, Mx, My, Mz), left(left), right(right), size(right - left + 1)
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

    data = new float[pc->pos.size() * 7];
    for(int i = 0; i < pc->pos.size(); ++i)
    {
        int base = i * 7;
        data[base + 0] = pc->pos[tmp[i]][0];
        data[base + 1] = pc->pos[tmp[i]][1];
        data[base + 2] = pc->pos[tmp[i]][2];
        data[base + 3] = pc->color[tmp[i]][0] / 255.0;
        data[base + 4] = pc->color[tmp[i]][1] / 255.0;
        data[base + 5] = pc->color[tmp[i]][2] / 255.0;
        data[base + 6] = 1;
    }
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

    Node* node = new Node(mx, my, mz, Mx, My, Mz, l, r);

    if(r != l)
    {
        node->son[0] = buildTree((index + 1) % 3, list, l, mid);
        node->son[1] = buildTree((index + 1) % 3, list, mid + 1, r);
    }

    return node;
}

bool KDTree::cmp(int l, int r)
{
    return sortPc->pos[l][sortIndex] < sortPc->pos[r][sortIndex];
}

int KDTree::fetchPoint(const Ogre::PlaneBoundedVolume* plane, std::shared_ptr<float> &result)
{
    result = NULL;
    updateModel = false;
    int offset = 0;
    int size = fetchPoint(root, plane, result, false, offset);
    if(updateModel)
    {
        result.reset(new float[size * 7]);
        fetchPoint(root, plane, result, true, offset);
    }
    if(updateModel)
        return size;
    else
        return -1;
}

int KDTree::fetchPoint(Node* now, const Ogre::PlaneBoundedVolume* plane, std::shared_ptr<float> &result, bool update, int &offset)
{
    int len = plane->planes.size();
    int allSelected = true;

    for(int i = 0; i < len; ++i)
    {
        Ogre::Plane::Side test = plane->planes[i].getSide(now->aabb);
        if(test == Ogre::Plane::NEGATIVE_SIDE)
        {
            if(update)
                now->last = 0;

            return 0;
        }

        if(test != Ogre::Plane::POSITIVE_SIDE)
            allSelected = false;
    }

    if(allSelected)
    {
        if(update)
        {
            now->last = now->size;
            memcpy(result.get() + offset, data + now->left * 7, now->size * 7 * sizeof(float));
            offset += now->size * 7;
        }
        else
        {
            if(now->last != now->size)
                updateModel = true;
        }

        return now->size;
    }

    int cnt = 0;
    if(now->son[0] != NULL)
        cnt += fetchPoint(now->son[0], plane, result, update, offset);
    if(now->son[1] != NULL)
        cnt += fetchPoint(now->son[1], plane, result, update, offset);

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