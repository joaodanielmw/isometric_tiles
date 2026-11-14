#ifndef APP_H_
#define APP_H_

#include <SDL3/SDL.h>
#include "macros.h"

typedef struct {
    SDL_Vertex vertices[GRID_WIDTH * GRID_HEIGHT * 4];
    int indices[GRID_WIDTH * GRID_HEIGHT * 6];
} Tiles;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    const bool *keyboard;
    Tiles tiles;
    bool running;
} AppState;

bool app_init(AppState *app);
void app_setup(AppState *app);
void app_handle_events(AppState *app, SDL_Event *event);
void app_update(AppState *app, float delta_time);
void app_render(AppState *app);
void app_quit(AppState *app);

#endif
