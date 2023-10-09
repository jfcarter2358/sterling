#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>
#include "point.h"
#include "triangle.h"

using namespace std;

class Model {
    public:
        Model();

        Point m_position;
        Point m_rotation;

        vector<Triangle> m_triangles;
};

#endif