#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include "student.h"

int init_gui(void);
void cleanup_gui(void);
int create_window(const char* title, int width, int height);
void render_students(SDL_Renderer* renderer, const StudentList* list);
void close_window(void);

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif
