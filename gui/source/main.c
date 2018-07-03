#include <stdio.h>
#include <string.h>

#include "app.h"
#include "menus.h"
#include "net.h"
#include "SDL_helper.h"
#include "touch.h"

static SceVoid Term_Services(SceVoid)
{
	sceCompatStop();
	sceCompatUninit();
	Net_Term();
	App_TermAppUtil();

    TTF_CloseFont(Ubuntu_R_large);
	TTF_CloseFont(Ubuntu_R);
	TTF_Quit();

	SDL_DestroyTexture(drive);
	SDL_DestroyTexture(banner);

    IMG_Quit();

	SDL_DestroyRenderer(RENDERER);
	SDL_DestroyWindow(WINDOW);

	SDL_Quit();
	sceKernelExitProcess(0);
}

static SceVoid Init_Services(SceVoid)
{
	SDL_Init(SDL_INIT_EVERYTHING);
    
    WINDOW = SDL_CreateWindow("VITAident-GUI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 544, SDL_WINDOW_SHOWN);
    RENDERER=SDL_CreateRenderer(WINDOW, -1,SDL_RENDERER_SOFTWARE);
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	SDL_LoadImage(RENDERER, &banner, "app0:sce_sys/icon0.png");
	SDL_LoadImage(RENDERER, &drive, "app0:sce_sys/res/drive.png");

    TTF_Init();
	Ubuntu_R = TTF_OpenFont("app0:sce_sys/res/Ubuntu-R.ttf", 22);
    Ubuntu_R_large = TTF_OpenFont("app0:sce_sys/res/Ubuntu-R.ttf", 25);

    if (!Ubuntu_R || !Ubuntu_R_large)
		Term_Services();
	
	App_InitAppUtil();
	Net_Init();
	sceCompatInitEx(0);
	sceCompatStart();
	Touch_Init();
}

int main(int argc, char *argv[]) 
{
	Init_Services();

	Menu_Main();
	
	Term_Services();

	return 0;
}