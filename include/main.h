#ifndef _main_h_
#define _main_h_

#include <switch.h>
#include <stdio.h>
#include <stdlib.h>
#include "MainMenu.h"
#include "botw_backend.h"
#include "mount.h"

int buttons;
int currentPage;
int maxPage;
int currentState;
int slot;
int keyboard;
int keyboardy;
int itemBox;
int isopen;
int drop;
char str[7];
int positionKey;
int key;
int number;
int currentItem;
int maxSlot;

int main(int argc, char **argv);
void startSDLServices();
void initServices();
void buttonLogic(int x);
void closeServices();
void MenuButtons(int x);
void MenuButtonsSlot(int x);
void ConfirmButton();
void setPages();
void KeyboardButtons(int x);
void BackButton();
void ItemMenu(int x);
void RupeeKey();
void comboBox(int x);
void dropMenuButtons(int x);
void KeyboardLogic();
void exitMen();
int file_exist (char *filename);
void getCaption();




#endif