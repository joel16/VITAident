#ifndef _VITAIDENT_SDL_HELPER_H_
#define _VITAIDENT_SDL_HELPER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *WINDOW;
SDL_Surface *WINDOW_SURFACE;
SDL_Renderer *RENDERER;
SDL_Texture *banner, *drive;
TTF_Font *Ubuntu_R_large, *Ubuntu_R;

static inline SDL_Color SDL_MakeColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Color colour = {r, g, b, a};
	return colour;
}

#define BACKGROUND_COLOUR      SDL_MakeColour(242, 241, 240, 255)
#define STATUS_BAR_COLOUR      SDL_MakeColour(69, 67, 62, 255)
#define MENU_BAR_COLOUR        SDL_MakeColour(255, 255, 255, 255)
#define ITEM_COLOUR            SDL_MakeColour(0, 0, 0, 255)
#define ITEM_SELECTED_COLOUR   MENU_BAR_COLOUR
#define MENU_SELECTOR_COLOUR   SDL_MakeColour(239, 118, 69, 255)
#define MENU_INFO_TITLE_COLOUR SDL_MakeColour(144, 137, 129, 255)
#define MENU_INFO_DESC_COLOUR  SDL_MakeColour(51, 51, 51, 255)

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour);
void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour);
void SDL_DrawText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char *text);
void SDL_LoadImage(SDL_Renderer *renderer, SDL_Texture **texture, char *path);
void SDL_DrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

#endif