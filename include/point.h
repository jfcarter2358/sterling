#pragma once

#ifndef _POINT_H_
#define _POINT_H_

#include <array>
#include "matrix.h"

using namespace std;

class Point {
    public:
        Point();
        Point(float, float, float);

        Matrix ToMatrix();
        void FromMatrix(Matrix);

        float m_x;
        float m_y;
        float m_z;

        Point Add(Point);
        Point Subtract(Point);
};

#endif