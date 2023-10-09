#include "point.h"

Point::Point() {
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Point::Point(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

Matrix Point::ToMatrix() {
    Matrix mat = Matrix(4, 1);
    mat.m_matrix[0][0] = m_x;
    mat.m_matrix[1][0] = m_y;
    mat.m_matrix[2][0] = m_z;
    mat.m_matrix[3][0] = 1;
 
    return mat;
}

void Point::FromMatrix(Matrix mat) {
    m_x = mat.m_matrix[0][0];
    m_y = mat.m_matrix[1][0];
    m_z = mat.m_matrix[2][0];
}

Point Point::Add(Point other) {
    Point output = Point();
    output.m_x = m_x + other.m_x;
    output.m_y = m_y + other.m_y;
    output.m_z = m_z + other.m_z;
    return output;
}

Point Point::Subtract(Point other) {
    Point output = Point();
    output.m_x = m_x - other.m_x;
    output.m_y = m_y - other.m_y;
    output.m_z = m_z - other.m_z;
    return output;
}