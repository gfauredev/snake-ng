#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
// #include <stdint.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

static SDL_Window*   window   = NULL;
static SDL_Renderer* renderer = NULL;

// This function runs once at startup
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("SnakeNG", "1.0", "snake-ng");
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("SnakeNG", WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                     &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

// This function runs when a new event (mouse input, keypresses, etc) occurs
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

// This function runs once per frame, it’s the heart of the program
SDL_AppResult SDL_AppIterate(void* appstate)
{
    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); // Set the whole window black

    SDL_Log("Displaying various flavors of hellos");
    SDL_SetRenderScale(renderer, 2.0f, 2.0f); // Double text size
    // Text white, then blue
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 20, 20, "Hello world!");
    SDL_SetRenderDrawColor(renderer, 32, 64, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 40, 40, "Hello blue!");

    SDL_SetRenderScale(renderer, 1.0f, 1.0f); // Reset text size
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White
    SDL_RenderDebugTextFormat(
        renderer, (float)((WINDOW_WIDTH - (charsize * 46)) / 2), 400,
        "(This program has been running for %" SDL_PRIu64 " seconds.)",
        SDL_GetTicks() / 1000);

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

// This function runs once at shutdown, SDL cleans the window/renderer
void SDL_AppQuit(void* appstate, SDL_AppResult result) {}
