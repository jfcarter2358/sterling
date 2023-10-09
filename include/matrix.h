#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <array>
#include <vector>
#include <math.h>

using namespace std;

class Matrix {
    public:
        Matrix();
        Matrix(int, int);
        Matrix Multiply(Matrix);
        static Matrix CreateFromYawPitchRoll(float, float, float);
        static Matrix CreateFromTranslation(float, float, float);
        
        vector<vector<float>> m_matrix;
};

#endif