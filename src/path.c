#include "path.h"
#include <SDL3/SDL.h>

bool path_open(char **path, const char *file){
    const char *base_path = SDL_GetBasePath();
    if(!SDL_asprintf(path, "%s%s", base_path, file))
        return false;
    return true;
}

void path_close(char *path){
    SDL_free(path);
}
