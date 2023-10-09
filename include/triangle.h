#pragma once

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <vector>
#include "point.h"
#include "screen.h"
#include "matrix.h"

using namespace std;

class Triangle {
    public:
        Triangle();        

        void Rotate(Matrix, Matrix, int, int);
        void Draw(Screen*, int, int);

        Point m_points[3];
        Point m_color;

        float m_displayX[3];
        float m_displayY[3];
};

#endif