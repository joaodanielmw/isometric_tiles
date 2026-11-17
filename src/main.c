#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include "app.h"

int main(int argc, char **argv){
    AppState app;
    SDL_Event event;
    float then, now, delta_time;

    if(!app_init(&app)){
        SDL_Log("Failed to initialize app. Exiting...");
        app_quit(&app);
        return EXIT_FAILURE;
    };
    
    app_setup(&app);

    then = SDL_GetTicks();
    while(app.running){ 
        now = SDL_GetTicks();
        delta_time = (now - then) / 1000.f;
        then = now;

        while(SDL_PollEvent(&event)) 
            app_handle_events(&app, &event);
        
        app_update(&app, delta_time);
        app_render(&app);
    }

    app_quit(&app);

    return EXIT_SUCCESS;
}
