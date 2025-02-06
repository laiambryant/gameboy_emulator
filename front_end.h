#include <SDL3/SDL.h>

typedef struct FrontEnd {
    SDL_Renderer* renderer;
    SDL_Window* window;
} FrontEnd;

#ifndef WINDOW_DEFAULTS
    #define DEFAULT_WINDOW_HEIGHT 800
    #define DEFAULT_WINDOW_WIDTH 600
#endif

int init_window();
int init_front_end(FrontEnd* front_end, const char* title);
SDL_Window* create_window(const char* title);
SDL_Renderer* create_renderer(SDL_Window* window, const char* title);
FrontEnd* create_front_end(const char* title);
int free_front_end(FrontEnd* front_end);
