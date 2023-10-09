#pragma once

#include "SDL2/SDL.h"

#ifndef _SCREEN_H_
#define _SCREEN_H_

using namespace std;

class Screen {
    public:
        int m_width = 1024;
        int m_height = 768;

        Screen();
        void InitColors();
        void UpdateTexture(SDL_Texture*);
        void DrawTexture(SDL_Renderer*, SDL_Texture*);

        Uint8 m_colors[1024][768][4];
        Uint32* m_pixels = nullptr;
        int m_pitch = 0;
};

#endif