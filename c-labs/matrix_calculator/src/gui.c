#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "../include/gui.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
static TTF_Font* font = NULL;

int init_gui(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL init error: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF init error: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    return 0;
}

int create_window(const char* title, int width, int height) {
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "Window error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Renderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }

    font = TTF_OpenFont("/opt/homebrew/share/fonts/DejaVuSans.ttf", 20);
    if (!font) {
        fprintf(stderr, "Font load warning\n");
    }

    return 0;
}

void render_students(SDL_Renderer* r, const StudentList* list) {
    if (!r || !list) return;

    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderClear(r);

    SDL_Color color = {0, 0, 0, 255};
    int y = 20;
    char buf[256];

    for (int i = 0; i < list->count && i < 10; i++) {
        snprintf(buf, sizeof(buf), "%s (%s) GPA: %.2f",
                 list->students[i].id,
                 list->students[i].name,
                 list->students[i].gpa);

        if (font) {
            SDL_Surface* s = TTF_RenderText_Solid(font, buf, color);
            SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
            SDL_Rect rect = {20, y, s->w, s->h};
            SDL_RenderCopy(r, t, NULL, &rect);
            SDL_FreeSurface(s);
            SDL_DestroyTexture(t);
        }

        y += 30;
    }

    SDL_RenderPresent(r);
}

void close_window(void) {
    if (font) {
        TTF_CloseFont(font);
        font = NULL;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

void cleanup_gui(void) {
    TTF_Quit();
    SDL_Quit();
}
