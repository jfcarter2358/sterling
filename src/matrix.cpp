#include "matrix.h"

Matrix::Matrix() {
    int rows = 4;
    int columns = 4;

    for (int i = 0; i < rows; i++) {
        vector<float> tempVect;
        for (int j = 0; j < columns; j++) {
            if (i == j) {
                tempVect.push_back(1);
            } else {
                tempVect.push_back(0);
            }
            m_matrix.push_back(tempVect);
        }
    }
}

Matrix::Matrix(int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        vector<float> tempVect;
        for (int j = 0; j < columns; j++) {
            tempVect.push_back(0);
        }
        m_matrix.push_back(tempVect);
    }
}

Matrix Matrix::Multiply(Matrix other) {
    int aRows = m_matrix.size();
    int bRows = other.m_matrix.size();
    int bColumns = other.m_matrix[0].size();

    Matrix output = Matrix(aRows, bColumns);
    float sum = 0;

    for (int c = 0; c < aRows; c++) {
        for (int d = 0; d < bColumns; d++) {
            for (int k = 0; k < bRows; k++) {
                sum = sum + m_matrix[c][k] * other.m_matrix[k][d];
            }
            output.m_matrix[c][d] = sum;
            sum = 0;
        }
    }

    return output;
}

Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll) {
    Matrix rotationXAxis = Matrix(4, 4);
    Matrix rotationYAxis = Matrix(4, 4);
    Matrix rotationZAxis = Matrix(4, 4);

    rotationXAxis.m_matrix[0][0] = 1;
    rotationXAxis.m_matrix[1][1] = (float)cos((double)pitch);
    rotationXAxis.m_matrix[1][2] = (float)-sin((double)pitch);
    rotationXAxis.m_matrix[2][1] = (float)sin((double)pitch);
    rotationXAxis.m_matrix[2][2] = (float)cos((double)pitch);
    rotationXAxis.m_matrix[3][3] = 1;
    
    rotationYAxis.m_matrix[0][0] = (float)cos((double)yaw);
    rotationYAxis.m_matrix[0][2] = (float)sin((double)yaw);
    rotationYAxis.m_matrix[1][1] = 1;
    rotationYAxis.m_matrix[2][0] = (float)-sin((double)yaw);
    rotationYAxis.m_matrix[2][2] = (float)cos((double)yaw);
    rotationYAxis.m_matrix[3][3] = 1;

    rotationZAxis.m_matrix[0][0] = (float)cos((double)roll);
    rotationZAxis.m_matrix[0][1] = (float)-sin((double)roll);
    rotationZAxis.m_matrix[1][0] = (float)sin((double)roll);
    rotationZAxis.m_matrix[1][1] = (float)cos((double)roll);
    rotationZAxis.m_matrix[2][2] = 1;
    rotationZAxis.m_matrix[3][3] = 1;

    Matrix result = rotationXAxis.Multiply(rotationYAxis).Multiply(rotationZAxis);

    return result;

}

Matrix Matrix::CreateFromTranslation(float x, float y, float z) {
    Matrix translation = Matrix();

    translation.m_matrix[0][3] = -x;
    translation.m_matrix[1][3] = -y;
    translation.m_matrix[2][3] = -z;

    return translation;
}