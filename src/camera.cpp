#include "camera.h"

Camera::Camera() {
    
}

void Camera::Init(float width, float height, float zNear, float zFar) {
    m_width = width;
    m_height = height;
    m_zNear = zNear;
    m_zFar = zFar;
    
    m_projection = Matrix(4, 4);
    
    m_projection.m_matrix[0][0] = 1.0f/m_width;
    m_projection.m_matrix[1][1] = 1.0f/m_height;
    m_projection.m_matrix[2][2] = -(2.0f)/(m_zFar - m_zNear);
    m_projection.m_matrix[3][2] = -(m_zFar + m_zNear)/(m_zFar - m_zNear);
    m_projection.m_matrix[3][3] = 1;
}
