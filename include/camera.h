#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <array>
#include "matrix.h"
#include "point.h"

using namespace std;

class Camera {
    public:
        Camera();
        void Init(float, float, float, float);

        Matrix m_projection;

        Point m_position;
        Point m_rotation;

        float m_width;
        float m_height;
        float m_zNear;
        float m_zFar;
};

#endif