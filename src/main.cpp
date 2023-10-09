#include "stdio.h"
#include "SDL2/SDL.h"
#include "screen.h"
#include "model.h"
#include "matrix.h"
#include "camera.h"
#include <vector>

#define QUITKEY SDLK_ESCAPE


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Event event;
SDL_Rect source, destination, dst;
SDL_Texture* texture;
Screen screen;
Camera camera;
float rotationSpeed = 0.01;
vector<Triangle> triangles;

int errorCount = 0;
int keyPressed;
int rectCount = 0;
float zNear = 1;
float zFar = 50;

void LoadCube(float x, float y, float z) {
    // Model model = Model();
    Point origin = Point(x, y, z);
    
    float corners[8][3] = {
        {1, 1, 1},
        {1, 1, -1},
        {1, -1, -1},
        {1, -1, 1},
        {-1, -1, 1},
        {-1, -1, -1},
        {1, 1, -1},
        {-1, 1, 1}
    };

    int triData[12][3] = {
        {0, 1, 3},
        {2, 3, 1},
        {3, 2, 4},
        {5, 4, 2},
        {4, 5, 7},
        {6, 7, 5},
        {7, 6, 0},
        {1, 0, 6},
        {0, 3, 7},
        {4, 7, 3},
        {5, 2, 6},
        {1, 6, 2}
    };

    for (int i = 0; i < 12; i++) {
        Triangle tri = Triangle();
        for (int j = 0; j < 3; j++){
            Point cornerOffset = Point(corners[triData[i][j]][0], corners[triData[i][j]][1], corners[triData[i][j]][2]);
            Point corner = origin.Add(cornerOffset);

            tri.m_points[j] = corner;
        }
        triangles.push_back(tri);
    }
}

void LogError(char* msg) {
    printf("%s\n", msg);
    errorCount++;
}

void SetCaption(char* msg) {
    SDL_SetWindowTitle(window, msg);
}

void InitSetup() {
    screen.InitColors();
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(screen.m_width, screen.m_height, SDL_WINDOW_SHOWN, &window, &renderer);
    if (!window) {
        LogError((char *)"InitSetup failed to create window");
    }
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screen.m_height, screen.m_width);
    SetCaption((char *)"Example");

    camera.m_position.m_x = 0;
    camera.m_position.m_y = -10;
    camera.m_position.m_z = 0;
    camera.m_rotation.m_x = 0;
    camera.m_rotation.m_y = 0;
    camera.m_rotation.m_z = 0;
    camera.Init(screen.m_width, screen.m_height, zNear, zFar);

    LoadCube(0, 0, 0);
}

char GetAChar() {
    int result = -1;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            result = event.key.keysym.sym;
            break;
        }
    }
    return result;
}

void GameLoop() {
    int gameRunning = 1;
    while (gameRunning) {
        Matrix view = Matrix::CreateFromYawPitchRoll(camera.m_rotation.m_x, camera.m_rotation.m_y, camera.m_rotation.m_z);
        
        Matrix projection = camera.m_projection;
        Matrix translation = Matrix::CreateFromTranslation(camera.m_position.m_x, camera.m_position.m_y, camera.m_position.m_z);

        Matrix viewProjectionTransform = view.Multiply(translation).Multiply(projection);

        
        for (int i = 0; i < triangles.size(); i++) {
            triangles[i].Rotate(camera.m_projection, viewProjectionTransform, screen.m_width, screen.m_height);
            triangles[i].Draw(&screen, screen.m_width, screen.m_height);
        }
        
        screen.UpdateTexture(texture);
        screen.DrawTexture(renderer, texture);

        while (SDL_PollEvent(&event)) {
            switch  (event.type) {
                case SDL_KEYDOWN: {
                    keyPressed = event.key.keysym.sym;
                    switch (keyPressed) {
                        case QUITKEY:
                            gameRunning = 0;
                            break; 
                        case SDLK_UP:
                            camera.m_rotation.m_y += rotationSpeed;
                            break;
                        case SDLK_DOWN:
                            camera.m_rotation.m_y -= rotationSpeed;
                            break;
                        case SDLK_LEFT:
                            camera.m_rotation.m_x -= rotationSpeed;
                            break;
                        case SDLK_RIGHT:
                            camera.m_rotation.m_x += rotationSpeed;
                            break;
                    }
                }
                break;
            }
        }
    }
}

void FinishOff() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}

int main(int argc, char* args[]) {
    InitSetup();
    GameLoop();
    FinishOff();
    return 0;
}