#include "MainMenu.h"


void selectSlotMenu(int slotchar){

	SDL_ClearScreen(renderer, BACKGROUND_COLOR);
	SDL_DrawRect(renderer,0,0,1280, 88, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,87,1220,2, WHITE_COLOR);
	SDL_DrawRect(renderer,0,648,1280,72, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	SDL_DrawText(Arial, 110, 27, WHITE_TEXT_COLOR, "Breath of the Wild Editor");

	SDL_DrawRect(renderer,380,148,517,400, LEFTBAR_COLOR);
	SDL_DrawText(Arial_S,554,200, WHITE_TEXT_COLOR, "Select File Slot:");
	
	char slotc[2];
	snprintf(slotc, sizeof slotc, "%d", slotchar);
	SDL_DrawText(Arial_S, 632, 230, WHITE_TEXT_COLOR, slotc);

	SDL_DrawImage(renderer, saveFileImg[slotchar],512, 300, 256, 144);

	SDL_RenderPresent(renderer);
}


void exitMenu(int pos){

	SDL_DrawRect(renderer, 380, 250, 520, 220, ALERT_COLOR);
	SDL_DrawText(Arial, 510, 300, WHITE_TEXT_COLOR, "Save Changes?");
	SDL_DrawText(Arial_M, 450, 350, WHITE_TEXT_COLOR, "A: Save X: Discard B: Return");
	SDL_RenderPresent(renderer);

}

void KeyboardScreen(){
	SDL_DrawImage(renderer, back, 0, 0, 1280, 720);
	SDL_DrawRect(renderer, 120, 30, 1040, 210, WHITE_COLOR);
	SDL_DrawRect(renderer, 122, 32, 1036, 206, BACKGROUND_COLOR);
	SDL_DrawRect(renderer, 0,270,1280,450, LEFTBAR_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	SDL_RenderPresent(renderer);
	showKeyboard(0);
}

void errorScreen(){

	SDL_ClearScreen(renderer, BACKGROUND_COLOR);
	SDL_DrawRect(renderer,0,0,1280, 88, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,87,1220,2, WHITE_COLOR);
	SDL_DrawRect(renderer,0,648,1280,72, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	SDL_DrawText(Arial, 110, 27, WHITE_TEXT_COLOR, "Breath of the Wild Editor");
	SDL_DrawRect(renderer,380,248,517,167, LEFTBAR_COLOR);
	SDL_DrawText(Arial_S,440,280, WHITE_TEXT_COLOR, "Error while mounting save directory!");
	SDL_DrawText(Arial_S,480,320, WHITE_TEXT_COLOR, "(Try launching BOTW before)");
	SDL_RenderPresent(renderer);
}


void showCurrentRup(){

	SDL_DrawImage(renderer, GreenRupee, 1077, 18, 35, 55);
	char rupString[10];
	snprintf(rupString, sizeof rupString, " : %d", (int)rupeeValue);
	SDL_DrawText(Arial_S, 1112, 33, WHITE_TEXT_COLOR, rupString);


}


void printText(int textNum){
	SDL_DrawRect(renderer, 122, 32, 1036, 206, BACKGROUND_COLOR);
	char tmpstring[8];
	snprintf(tmpstring, sizeof tmpstring, "%d", textNum);
	SDL_DrawText(Arial, 125, 110, WHITE_TEXT_COLOR, tmpstring);
	SDL_RenderPresent(renderer);
}

void mainUI(int x, int currentPage, int maxPage, int showBox, int BoxPos){

	SDL_ClearScreen(renderer, BACKGROUND_COLOR);
	SDL_DrawRect(renderer,0,0,1280, 88, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,87,1220,2, WHITE_COLOR);
	SDL_DrawRect(renderer,0,89,410,560, LEFTBAR_COLOR);
	SDL_DrawRect(renderer,410,89,880,560, TOPBAR_COLOR);
	SDL_DrawRect(renderer,0,648,1280,72, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	SDL_DrawText(Arial, 110, 27, WHITE_TEXT_COLOR, "Breath of the Wild Editor");

	setMenuItems(x, currentPage);

	showCurrentRup();

	setPageBar(currentPage, maxPage);

	if(showBox){
		showBoxSelect(BoxPos);
	}

	int selectedItem = (5 * (currentPage - 1) + x);

	isArrow = 0;

	for(int i = 0; i < 6; i++){
		if(getIDNumber(itemName[selectedItem]) >= 192){
			isArrow = 1;
			break;
		}
	}

	if(isArrow && newQuantItems[selectedItem] >= 999){
		newQuantItems[selectedItem] = 999;
	}

	if(selectedItem <= numberOfItems - 1){
		showItemSDL(selectedItem, isArrow);
	}
	SDL_RenderPresent(renderer);
}


void showKeyboard(int currentKey){

	char populateKeyboard[9][2] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

	for(int y = 0; y < 3; y++){
		for(int x = 0; x < 3; x++){

			if((x + (y * 3)) == currentKey){
				SDL_DrawRect(renderer, 470 + (x * 110), 300 + (y * 80), 105, 75, TOPBAR_COLOR);
				SDL_DrawText(Arial, 510 + (x * 110), 320 + (y * 80), BLUE_TEXT_COLOR, populateKeyboard[x + (y * 3)]);
			} 	
			else{
				SDL_DrawRect(renderer, 470 + (x * 110), 300 + (y * 80), 105, 75, ITEM_COLOR);
				SDL_DrawText(Arial, 510 + (x * 110), 320 + (y * 80), WHITE_TEXT_COLOR, populateKeyboard[x + (y * 3)]);
			}
				
		}
	}

	if(currentKey == 9){
		SDL_DrawImage(renderer, bbuttonp, 470, 540, 105, 75);
	}
	else{
		SDL_DrawImage(renderer, bbutton, 470, 540, 105, 75);
	}
	
	if(currentKey == 11){
		SDL_DrawImage(renderer, okbuttonp, 690, 540, 105, 75);
	}
	else{
		SDL_DrawImage(renderer, okbutton, 690, 540, 105, 75);
	}

	if(currentKey == 10){
		SDL_DrawRect(renderer, 580, 540, 105, 75, TOPBAR_COLOR);
		SDL_DrawText(Arial, 620, 560, BLUE_TEXT_COLOR, "0");
	}
	else{
		SDL_DrawRect(renderer, 580, 540, 105, 75, ITEM_COLOR);
		SDL_DrawText(Arial, 620, 560, WHITE_TEXT_COLOR, "0");
	}
	
	


	SDL_RenderPresent(renderer);


}


void showBoxSelect(int pos){
	if(pos == 1){
		SDL_DrawRect(renderer, 465, 237, 760, 70, BLUE_TEXT_COLOR);
		SDL_DrawRect(renderer, 470, 240, 750, 60, TOPBAR_COLOR);
	}
	if(pos == 2){
		SDL_DrawRect(renderer, 465, 317, 760, 70, BLUE_TEXT_COLOR);
		SDL_DrawRect(renderer, 470, 320, 750, 60, TOPBAR_COLOR);
	}
	
}




void showItemSDL(int currentItem, int arrow){

	SDL_DrawRect(renderer, 470, 140, 750, 3, LEFTBAR_COLOR);
	SDL_DrawText(Arial, 480, 150, WHITE_TEXT_COLOR, translate(itemName[currentItem]));
	SDL_DrawRect(renderer, 470, 200, 750, 3, LEFTBAR_COLOR);

	char value[25];
	snprintf(value, sizeof value, "%d", (int)newQuantItems[currentItem]);

	SDL_DrawRect(renderer, 470, 240, 750, 3, LEFTBAR_COLOR);
	SDL_DrawText(Arial_M, 480, 252, WHITE_TEXT_COLOR, "Quantity");
	SDL_DrawText(Arial_M, 1100, 252, BLUE_TEXT_COLOR, value);
	SDL_DrawRect(renderer, 470, 300, 750, 3, LEFTBAR_COLOR);

	char othervalue[25];
	if(strcmp(translateMods(new_modNames[currentItem]), "(none)")==0){
			new_quantMod[currentItem] = 0;
	}
	snprintf(othervalue, sizeof othervalue, "%d", (int)new_quantMod[currentItem]);

	if(arrow == 0){
		SDL_DrawRect(renderer, 470, 320, 750, 3, LEFTBAR_COLOR);
		SDL_DrawText(Arial_M, 480, 332, WHITE_TEXT_COLOR, translateMods(new_modNames[currentItem]));
		SDL_DrawText(Arial_M, 1100, 332, BLUE_TEXT_COLOR, othervalue);
		SDL_DrawRect(renderer, 470, 380, 750, 3, LEFTBAR_COLOR);
	}

	

}


void Show_DropDownMenu(int pos){
	SDL_DrawRect(renderer,0,360,1280,360, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,432,1220,2, WHITE_COLOR);
	SDL_DrawRect(renderer,300,540,620,2, WHITE_TEXT_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	
	if(pos == 1){
		SDL_DrawRect(renderer, 300, 440, 620, 98, BLUE_TEXT_COLOR);
		SDL_DrawRect(renderer, 304, 444, 612, 90, TOPBAR_COLOR);
	}
	else if(pos == 2){
		SDL_DrawRect(renderer, 300, 548, 620, 98, BLUE_TEXT_COLOR);
		SDL_DrawRect(renderer, 304, 552, 612, 90, TOPBAR_COLOR);
	}
	SDL_DrawText(Arial_M, 500, 475, WHITE_TEXT_COLOR, "Edit Modifier");
	SDL_DrawText(Arial_M, 500, 580, WHITE_TEXT_COLOR, "Edit Quantity");

	SDL_RenderPresent(renderer);

}

void Show_DropDownMenuMod(int pos){

	SDL_ClearScreen(renderer, BACKGROUND_COLOR);

	SDL_DrawRect(renderer,0,0,1280, 88, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,87,1220,2, WHITE_COLOR);
	SDL_DrawRect(renderer,0,648,1280,72, TOPBAR_COLOR);
	SDL_DrawRect(renderer,30,648,1220,2, WHITE_COLOR);
	SDL_DrawText(Arial, 110, 27, WHITE_TEXT_COLOR, "Breath of the Wild Editor");
	
	int offset = 95;

	char modifierNames[17][28] = {
	"(none)",
	"Attack up",
	"Attack up *",
	"Durability up",
	"Durability up *",
	"Critical hit up",
	"Critical hit up*",
	"Long throw * (Weapon)",
	"Long throw * (Weapon)",
	"Five-Shot Burst (Bow)",
	"Five-Shot Burst* (Bow)",
	"Quick shot (Bow)",
	"Quick shot * (Bow)",
	"Shield surf up (Shield)",
	"Shield surf up * (Shield)",
	"Shield guard up (Shield)",
	"Shield guard up * (Shield)"
	};

	for(int x = 0; x < 17; x++){
		if(x == pos){
			SDL_DrawImage(renderer, check, 50, offset + (x * 32), 32, 32);
			SDL_DrawText(Arial_M, 100, offset + (x * 32), BLUE_TEXT_COLOR, modifierNames[x]);
		}
		else{
			SDL_DrawText(Arial_M, 100, offset + (x * 32), WHITE_TEXT_COLOR, modifierNames[x]);
		}
	}

	SDL_RenderPresent(renderer);

}



void SDL_ClearScreen(SDL_Renderer* renderer, SDL_Color colour)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
	SDL_RenderClear(renderer);
}

void setPageBar(int page, int mPage){
	char pageText[15];
	snprintf(pageText, sizeof pageText, "Page (%d/%d)", page, mPage);
    SDL_DrawText(Arial_S, 30, 670, WHITE_TEXT_COLOR, pageText);
}

void setMenuItems(int active, int page){

    int offset = 100;
    for(int x = 0; x < 5; x++)
    {
    	

    	if(((5 * (page - 1)) + x) < numberOfItems){
    		if(x == active){
    		 	SDL_DrawRect(renderer, 30, 25 + (offset * (x+1)), 5, 80, BLUE_TEXT_COLOR);
    		 	SDL_DrawText(Arial_S, 120, offset * (x+1) + 50,BLUE_TEXT_COLOR, translate(itemName[(5 * (page - 1)) + x])); 
    	
    		}
    		else{
    		 	//SDL_DrawRect(renderer, 25, 25 + (offset * (x+1)), 350, 80, ITEM_COLOR);
    		 	SDL_DrawText(Arial_S, 120, offset * (x+1) + 50,WHITE_TEXT_COLOR, translate(itemName[(5 * (page - 1)) + x])); 
    		}
    		
    		SDL_DrawImage(renderer, sprites[getIDNumber(itemName[(5 * (page - 1)) + x])], 50,  35 + (offset * (x+1)) , 50, 50);
    	}


    }

}

SDL_Surface *SDL_LoadImage(SDL_Renderer* renderer, SDL_Texture **texture, char *path)
{
	SDL_Surface *loaded_surface = NULL;
	loaded_surface = IMG_Load(path);

	if (loaded_surface)
	{
		Uint32 colorkey = SDL_MapRGB(loaded_surface->format, 0, 0, 0);
		SDL_SetColorKey(loaded_surface, SDL_TRUE, colorkey);
		*texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	}

	SDL_FreeSurface(loaded_surface);
	return NULL;
}

void SDL_DrawImage(SDL_Renderer* renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect viewport;
	viewport.x = x; viewport.y = y; viewport.w = w; viewport.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &viewport);
}


void SDL_DrawRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color colour)
{
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void SDL_DrawText(TTF_Font *font, int x, int y, SDL_Color colour, const char *text)
{
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, colour, 1280);
	SDL_SetSurfaceAlphaMod(surface, 255);
	SDL_Rect position = {x, y, surface->w, surface->h};
	SDL_BlitSurface(surface, NULL, screenSurface, &position);
	SDL_FreeSurface(surface);
}

