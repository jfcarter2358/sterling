#include "triangle.h"

Triangle::Triangle() {

}

void Triangle::Rotate(Matrix projection, Matrix viewProjectionTransform, int WIDTH, int HEIGHT) {
    for (int i = 0; i < 3; i++) {   
        Matrix pointMatrix = m_points[i].ToMatrix();
        Matrix vptPointMatrix = viewProjectionTransform.Multiply(pointMatrix);
        Matrix displayMatrix = projection.Multiply(vptPointMatrix);
        
        float rotateX = displayMatrix.m_matrix[0][0];
        float rotateY = displayMatrix.m_matrix[1][0];
        float rotateZ = displayMatrix.m_matrix[2][0];
        float rotateW = displayMatrix.m_matrix[3][0];

        m_displayX[i] = (rotateX + (float)WIDTH) / (2 * rotateW) + (0.5 * WIDTH);
        m_displayY[i] = (rotateY + (float)HEIGHT) / (2 * rotateW) + (0.5 * HEIGHT);
    }
}

void Triangle::Draw(Screen *screen, int WIDTH, int HEIGHT) {
    for (int i = 0; i < 3; i++) {
        if (m_displayX[i] > 0 && m_displayX[i] < WIDTH) {
            if (m_displayY[i] > 0 && m_displayY[i] < HEIGHT) {
                screen->m_colors[(int)m_displayX[i]][(int)m_displayY[i]][0] = 255;
            }
        }
    }
}