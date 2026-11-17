#include "app.h"
#include "path.h"
#include <SDL3_image/SDL_image.h>

static void tile_setup_vertices(SDL_Vertex vertices[], uint32_t idx, float x, float y){
    uint32_t vert_offset = idx * 4;

    float corner_table[][2] = {     
        { 0.f, 0.f },
        { 1.f, 0.f },
        { 1.f, 1.f },
        { 0.f, 1.f }
    };

    for(int i = 0; i < 4; i++){
        vertices[vert_offset + i].position.x = TRANSLATE_X(x + corner_table[i][0], y + corner_table[i][1]);
        vertices[vert_offset + i].position.y = TRANSLATE_Y(x + corner_table[i][0], y + corner_table[i][1]);
    }
}

static void tile_setup_indices(int indices[], uint32_t idx){
    uint32_t vert_offset = idx * 4;
    uint32_t index_offset = idx * 6;
    
    int index_table[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    for(int i = 0; i < 6; i++) 
        indices[index_offset + i] = index_table[i] + vert_offset;
}

static void tile_setup_color(SDL_Vertex vertices[], uint32_t idx){
    uint32_t vert_offset = idx * 4;
    for(int i = 0; i < 4; i++)
            vertices[vert_offset + i].color = (SDL_FColor){ 1.f, 1.f, 1.f, 1.f };
}

static void tile_setup_texture_uv(SDL_Vertex vertices[], uint32_t idx, SDL_FRect src_rect, int tw, int th){
    uint32_t vert_offset = idx * 4;
    float u0 = src_rect.x / tw;
    float v0 = src_rect.y / th;
    float u1 = (src_rect.x + src_rect.w) / tw;
    float v1 = (src_rect.y + src_rect.h) / th;
    
    float corner_table[][2] = {     
        { u0, v0 },
        { u1, v0 },
        { u1, v1 },
        { u0, v1 }
    };

    for(int i = 0; i < 4; i++){
        vertices[vert_offset + i].tex_coord.x = corner_table[i][0];
        vertices[vert_offset + i].tex_coord.y = corner_table[i][1];
    }
}

static void app_setup_map(AppState *app){
    uint32_t idx;
    SDL_FRect src_rect = { 0., 16.f, 16.f, 16.f };

    for(int x = 0; x < GRID_WIDTH; x++){
        for(int y = 0; y < GRID_HEIGHT; y++){
            idx = y * GRID_WIDTH + x;
            tile_setup_vertices(app->tiles.vertices, idx, x, y);
            tile_setup_indices(app->tiles.indices, idx);
            tile_setup_color(app->tiles.vertices, idx);
            tile_setup_texture_uv(app->tiles.vertices, idx, src_rect, app->atlas->w, app->atlas->h);
        }
    }
}

//

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

    app->atlas = NULL;
    
    char *path;
    if(path_open(&path, "assets/terrain.png")){
        app->atlas = IMG_LoadTexture(app->renderer, path);
        path_close(path);
    }

    if(!app->atlas) {
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "app_init.IMG_LoadTexture: %s", SDL_GetError());
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
        app->atlas,
        app->tiles.vertices,
        GRID_WIDTH * GRID_HEIGHT * 4,
        app->tiles.indices,
        GRID_WIDTH * GRID_HEIGHT * 6
    );

    SDL_RenderPresent(app->renderer);
}

void app_quit(AppState *app){
    if(app->atlas) SDL_DestroyTexture(app->atlas);
    if(app->renderer) SDL_DestroyRenderer(app->renderer);
    if(app->window) SDL_DestroyWindow(app->window);
    SDL_Quit();
}
