#include "app.h"

static void tile_setup(SDL_Vertex *vertices, int *indices, uint32_t idx, float x, float y){
    float corner_table[][2] = {     
        { 0.f, 0.f },
        { 1.f, 0.f },
        { 1.f, 1.f },
        { 0.f, 1.f }
    };

    int index_table[] = {
        0, 1, 2,
        2, 3, 0
    };

    SDL_FColor color_table[] = {
        {1.f, 0.f, 0.f, 1.f},
        {0.f, 1.f, 0.f, 1.f},
        {0.f, 0.f, 1.f, 1.f},
        {0.f, 0.f, 0.f, 1.f},
    };

    uint32_t vert_offset = idx * 4;
    uint32_t index_offset = idx * 6;

    for(int i = 0; i < 4; i++){
        vertices[vert_offset + i].position.x = TRANSLATE_X(x + corner_table[i][0], y + corner_table[i][1]);
        vertices[vert_offset + i].position.y = TRANSLATE_Y(x + corner_table[i][0], y + corner_table[i][1]);
        vertices[vert_offset + i].color = color_table[i];

    }

    for(int i = 0; i < 6; i++) {
        indices[index_offset + i] = vert_offset + index_table[i];
    }
}

static void app_setup_map(AppState *app){
    for(int x = 0; x < GRID_WIDTH; x++){
        for(int y = 0; y < GRID_HEIGHT; y++){
            tile_setup(
                app->tiles.vertices,
                app->tiles.indices,
                y * GRID_WIDTH + x,
                x, y
            );
        }
    }
}

bool app_init(AppState *app){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "app_init.SDL_Init: %s", SDL_GetError());
        return false;
    }

    if(!SDL_CreateWindowAndRenderer(
       "Isometric Tiles",
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE,
        &(app->window),
        &(app->renderer)
    )){
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "app_init.SDL_CreateWindowAndRenderer: %s", SDL_GetError());
        return false;
    }

    app->keyboard = SDL_GetKeyboardState(NULL);
    app->running = true;

    return true;
}

void app_setup(AppState *app){
    app_setup_map(app);
}

void app_handle_events(AppState *app, SDL_Event *event){
    switch(event->type){
        case SDL_EVENT_QUIT:
            app->running = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            if(event->key.key == SDLK_ESCAPE)
                app->running = false;
            break;
    }
}

void app_update(AppState *app, float delta_time){
    // TODO:
    // - Use this for something
}

void app_render(AppState *app){
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderGeometry(
        app->renderer,
        NULL,
        app->tiles.vertices,
        GRID_WIDTH * GRID_HEIGHT * 4,
        app->tiles.indices,
        GRID_WIDTH * GRID_HEIGHT * 6
    );

    SDL_RenderPresent(app->renderer);
}

void app_quit(AppState *app){
    if(app->renderer) SDL_DestroyRenderer(app->renderer);
    if(app->window) SDL_DestroyWindow(app->window);
    SDL_Quit();
}
