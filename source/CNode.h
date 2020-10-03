#pragma once
#include"CPunto.h"
#include<vector>

enum { WHITE = 0, BLACK = 1, GRAY = 2 };
#define COLOR int


class CNode {
public:
    CNode() {
        parent = NULL;
        color = WHITE;
        volume = 0;
    }

    CNode(int octant_vol, CPunto offset, CPunto size, CNode* parent_ = NULL) {
        boundfp = offset;
        boundsp = boundfp + size;
        chSize = CPunto(size.x * 0.5, size.y * 0.5, size.z * 0.5);
        parent = parent_;
        color = WHITE;
        volume = octant_vol;
    }

    bool isInside(CPunto apoint) {
        return (boundfp.x <= apoint.x && boundsp.x > apoint.x) &&
            (boundfp.y <= apoint.y && boundsp.y > apoint.y) &&
            (boundfp.z <= apoint.z && boundsp.z > apoint.z);
    }

    bool isInStopCriterion(double fullCapacity) {
        return int(volume * fullCapacity) <= int(content.size());
    }


    CNode* hijos[8] = { NULL };

    CNode* parent;
    COLOR color;

    vector<CPunto*> content;
    CPunto boundfp, boundsp;

    CPunto chSize;
    int volume;
};