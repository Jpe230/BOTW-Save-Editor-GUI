#ifndef _MAINMENU_H_
#define _MAINMENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "translations.h"
#include "botw_backend.h"

SDL_Window* window;
SDL_Surface* screenSurface;
SDL_Renderer* renderer;
TTF_Font *Arial, *Arial_S, *Arial_M;
SDL_Texture *sprites[200];
SDL_Texture *GreenRupee;
SDL_Texture *back;
SDL_Texture *bbutton;
SDL_Texture *okbutton;
SDL_Texture *bbuttonp;
SDL_Texture *okbuttonp;
SDL_Texture *check;

int isArrow;


static inline SDL_Color SDL_MakeColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color colour = {r, g, b};
	return colour;
}


#define TOPBAR_COLOR SDL_MakeColor(45,45,45)
#define ALERT_COLOR SDL_MakeColor(32,32,32)
#define LEFTBAR_COLOR SDL_MakeColor(50,50,50)
#define BACKGROUND_COLOR SDL_MakeColor(45,45,45)
#define ITEM_COLOR SDL_MakeColor(47,47,47)
#define WHITE_TEXT_COLOR SDL_MakeColor(235,235,235)
#define WHITE_COLOR SDL_MakeColor(254, 254, 254)
#define BLACK_COLOR SDL_MakeColor(1,1,1)
#define BLUE_TEXT_COLOR SDL_MakeColor(1,254,203)



void SDL_ClearScreen(SDL_Renderer* renderer, SDL_Color colour);
void SDL_DrawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color colour);
void SDL_DrawText(TTF_Font *font, int x, int y, SDL_Color colour, const char *text);
void setMenuItems(int x, int page);
void setPageBar(int page, int mPage);
void mainUI(int x, int currentPage, int MaxPage,int showBox, int BoxPos);
SDL_Surface *SDL_LoadImage(SDL_Renderer* renderer, SDL_Texture **texture, char *path);
void SDL_DrawImage(SDL_Renderer* renderer, SDL_Texture *texture, int x, int y, int w, int h);
void showItemSDL(int currentItem, int arrow);
void selectSlotMenu(int slotchar);
void showKeyboard(int currentKey);
void errorScreen();
void showKeyboard();
void showCurrentRup();
void KeyboardScreen();
void showBoxSelect(int pos);
void Show_DropDownMenu(int pos);
void Show_DropDownMenuMod(int pos);
void printText(int textNum);
void exitMenu(int pos);

#endif
