#include "screen.h"

Screen::Screen() {

}

void Screen::InitColors() {
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            float g = (Uint8)(((float)x / m_width) * 255);
            float b = (Uint8)(((float)y / m_height) * 255);    
            m_colors[x][y][0] = 0;
            m_colors[x][y][1] = 0;
            m_colors[x][y][2] = 0;
            // m_colors[x][y][1] = g;
            // m_colors[x][y][2] = b;
            m_colors[x][y][3] = 255;
        }
    }
}



void Screen::UpdateTexture(SDL_Texture* texture) {
    Uint32 format;
    Uint8 *src;
    Uint32 *dst;
    int row, col;
    void *pixels;
    int pitch;

    int w, h;
    SDL_QueryTexture(texture, &format, nullptr, &w, &h);
    
    //if (SDL_LockTexture(texture, NULL, (void **)&m_pixels, &m_pitch)) {
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s\n", SDL_GetError());
    }
    
    SDL_PixelFormat pixelFormat;
    pixelFormat.format = format;
    
    for (row = 0; row < m_height; ++row) {
        dst = (Uint32 *)((Uint8 *)pixels + row * pitch);
        for (col = 0; col < m_width; ++col) {
            SDL_Color color = {m_colors[col][row][0], m_colors[col][row][1], m_colors[col][row][2], 255};
            // SDL_Color color = {255, 255, 255, 255};
            *dst++ = (0xFF000000 | (color.r << 16) | (color.g << 8) | (color.b));
        }
    }
    /*
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            Uint32 idx = y * (m_pitch / sizeof(unsigned int)) + x;      
            // Uint32 color = SDL_MapRGB(&pixelFormat, m_pixels[x][y][0], m_pixels[x][y][1], m_pixels[x][y][2]);
            Uint32 color = SDL_MapRGB(&pixelFormat, 1, 1, 1);
            m_pixels[idx] = color;
        }
    }
    */
    
    SDL_UnlockTexture(texture);
}

void Screen::DrawTexture(SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = m_width;
    rect.h = m_height;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}