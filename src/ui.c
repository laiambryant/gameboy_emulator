#include "ui.h"
#include "emu.h"
#include "bus.h"
#include "ppu.h"
#include "gamepad.h"

#include <SDL3/SDL.h>

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;
SDL_Texture *sdlTexture;
SDL_Surface *screen;

SDL_Window *sdlDebugWindow;
SDL_Renderer *sdlDebugRenderer;
SDL_Texture *sdlDebugTexture;
SDL_Surface *debugScreen;

static int scale = 3;

void ui_init() {
    
    SDL_Init(SDL_INIT_VIDEO);
    printf("SDL INIT\n");

    SDL_CreateWindowAndRenderer("Window", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdlWindow, &sdlRenderer);

    screen = SDL_CreateSurface(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_PIXELFORMAT_RGBA8888);
    sdlTexture = SDL_CreateTexture(sdlRenderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
                                                SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_CreateWindowAndRenderer("Debug Window", 16 * 8 * scale, 32 * 8 * scale, 0, 
        &sdlDebugWindow, &sdlDebugRenderer);

    debugScreen = SDL_CreateSurface( (16 * 8 * scale) + (16 * scale),
                                            (32 * 8 * scale) + (64 * scale), SDL_PIXELFORMAT_RGBA8888);

    sdlDebugTexture = SDL_CreateTexture(sdlDebugRenderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
                                            (16 * 8 * scale) + (16 * scale), 
                                            (32 * 8 * scale) + (64 * scale));

    int x, y;
    SDL_GetWindowPosition(sdlWindow, &x, &y);
    SDL_SetWindowPosition(sdlDebugWindow, x + SCREEN_WIDTH + 10, y);
}

void delay(u32 ms) {
    SDL_Delay(ms);
}

u32 get_ticks() {
    return SDL_GetTicks();
}

static unsigned long tile_colors[4] = {0xFFFFFFFF, 0xFFAAAAAA, 0xFF555555, 0xFF000000}; 

void display_tile(SDL_Surface *surface, u16 startLocation, u16 tileNum, int x, int y) {
    SDL_Rect rc;

    for (int tileY=0; tileY<16; tileY += 2) {
        u8 b1 = bus_read(startLocation + (tileNum * 16) + tileY);
        u8 b2 = bus_read(startLocation + (tileNum * 16) + tileY + 1);

        for (int bit=7; bit >= 0; bit--) {
            u8 hi = !!(b1 & (1 << bit)) << 1;
            u8 lo = !!(b2 & (1 << bit));

            u8 color = hi | lo;

            rc.x = x + ((7 - bit) * scale);
            rc.y = y + (tileY / 2 * scale);
            rc.w = scale;
            rc.h = scale;

            SDL_FillSurfaceRect(surface, &rc, tile_colors[color]);
        }
    }
}

void update_dbg_window() {
    int xDraw = 0;
    int yDraw = 0;
    int tileNum = 0;

    SDL_Rect rc;
    rc.x = 0;
    rc.y = 0;
    rc.w = debugScreen->w;
    rc.h = debugScreen->h;
    SDL_FillSurfaceRect(debugScreen, &rc, 0xFF111111);

    u16 addr = 0x8000;

    for (int y=0; y<24; y++) {
        for (int x=0; x<16; x++) {
            display_tile(debugScreen, addr, tileNum, xDraw + (x * scale), yDraw + (y * scale));
            xDraw += (8 * scale);
            tileNum++;
        }

        yDraw += (8 * scale);
        xDraw = 0;
    }

	SDL_UpdateTexture(sdlDebugTexture, NULL, debugScreen->pixels, debugScreen->pitch);
	SDL_RenderClear(sdlDebugRenderer);
	SDL_RenderTexture(sdlDebugRenderer, sdlDebugTexture, NULL, NULL);
	SDL_RenderPresent(sdlDebugRenderer);
}

void ui_update() {
    SDL_Rect rc;
    rc.x = rc.y = 0;
    rc.w = rc.h = 2048;

    u32 *video_buffer = ppu_get_context()->video_buffer;

    for (int line_num = 0; line_num < YRES; line_num++) {
        for (int x = 0; x < XRES; x++) {
            rc.x = x * scale;
            rc.y = line_num * scale;
            rc.w = scale;
            rc.h = scale;

            SDL_FillSurfaceRect(screen, &rc, video_buffer[x + (line_num * XRES)]);
        }
    }

    SDL_UpdateTexture(sdlTexture, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderTexture(sdlRenderer, sdlTexture, NULL, NULL);
    SDL_RenderPresent(sdlRenderer);

    update_dbg_window();
}

void ui_on_key(bool down, u32 key_code) {

    switch(key_code) {
        case SDLK_Z: gamepad_get_state()->b = down; break;
        case SDLK_X: gamepad_get_state()->a = down; break;
        case SDLK_RETURN: gamepad_get_state()->start = down; break;
        case SDLK_TAB: gamepad_get_state()->select = down; break;
        case SDLK_UP: gamepad_get_state()->up = down; break;
        case SDLK_DOWN: gamepad_get_state()->down = down; break;
        case SDLK_LEFT: gamepad_get_state()->left = down; break;
        case SDLK_RIGHT: gamepad_get_state()->right = down; break;
    }

}

void ui_handle_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0)
    {
        if (e.type == SDL_EVENT_KEY_DOWN) {
            ui_on_key(true, e.key.down);
        }

        if (e.type == SDL_EVENT_KEY_DOWN) {
            ui_on_key(false, e.key.down);
        }

        if (e.window.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            emu_get_context()->die = true;
        }
    }
}

