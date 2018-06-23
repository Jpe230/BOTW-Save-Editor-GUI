#include "main.h"

void startSDLServices(){
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    
    Arial = TTF_OpenFont("romfs:/arial.ttf", 36);
    Arial_M = TTF_OpenFont("romfs:/arial.ttf", 30);
    Arial_S = TTF_OpenFont("romfs:/arial.ttf", 24);

    positionKey = 0;
    
    SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
    screenSurface = SDL_GetWindowSurface(window);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    IMG_Init(IMG_INIT_PNG);
    
    for(int x = 0; x < 198; x++){
        char nameFile[50];
        snprintf(nameFile, sizeof nameFile, "romfs:/sprites/0_%02d.png", x+1);
        SDL_LoadImage(renderer, &sprites[x], nameFile);
    }

    SDL_LoadImage(renderer, &GreenRupee, "romfs:/gr.png");
    SDL_LoadImage(renderer, &back, "romfs:/back.png");
    SDL_LoadImage(renderer, &bbutton, "romfs:/bbutton.png");
    SDL_LoadImage(renderer, &okbutton,"romfs:/okbutton.png" );
    SDL_LoadImage(renderer, &bbuttonp, "romfs:/bbutton_p.png");
    SDL_LoadImage(renderer, &okbuttonp,"romfs:/okbutton_p.png" );
    SDL_LoadImage(renderer, &check,"romfs:/check.png" );

    if(mountSaveData() == 0){
        currentState = -1;
         errorScreen();
    }
    else{
        if (file_exist("save:/6/caption.jpg"))
            maxSlot = 7;
        else
            maxSlot = 5;
        getCaption();
        selectSlotMenu(slot);
    }
    
}


void getCaption(){
    for(int x = 0; x < (maxSlot + 1); x++){
        char nameFile_S[29];
        snprintf(nameFile_S, sizeof nameFile_S, "save:/%d/caption.jpg", x);
        
        if(file_exist (nameFile_S)){
            SDL_LoadImage(renderer, &saveFileImg[x], nameFile_S);
        }
        else{
            SDL_LoadImage(renderer, &saveFileImg[x], "romfs:/missingSlot.png");
        }
    }
}

int file_exist (char *filename)
{   
    FILE *file = fopen(filename, "r");
   if (file != NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void initServices(){
    buttons = 0;
    slot = 0;
    currentPage = 1;
    currentState = 0;
    currentItem = 0;
    romfsInit();
    startSDLServices();
}

void setPages(){

    maxPage = numberOfItems/5;
    
    if(numberOfItems%5 != 0){
        maxPage++;
    }
}


void buttonLogic(int x){
    switch(currentState){
        case 0:
            MenuButtonsSlot(x);
            break;
        case 1:
            MenuButtons(x);
            break;
        case 2:
            ItemMenu(x);
            break;
        case 3:
            comboBox(x);
            break;
        case 4:
            dropMenuButtons(x);
            break;
        case 7:
            KeyboardButtons(x);
            break;
        case 8:
            KeyboardButtons(x);
            break;
        case 9:
            KeyboardButtons(x);
            break;
    }

}

void comboBox(int x){
    switch(x){
        case 0:
            itemBox = 1;
            break;
        case 1:
            itemBox = 2;
            break;
    }
    Show_DropDownMenu(itemBox);
}

void ItemMenu(int x){
    switch(x){
        case 0:
            itemBox = 1;
            break;
        case 1:
            itemBox = 2;
            break;
    }
    if(isArrow == 1){
        itemBox = 1;
    }
    mainUI(buttons, currentPage, maxPage,1,itemBox);

}

void BackButton(){
    switch(currentState){
        case 2:
            currentState--;
            mainUI(buttons, currentPage, maxPage,0,0);
            break;

        case 3:
            currentState--;
            mainUI(buttons, currentPage, maxPage,1,1);
            break;

        case 4:
            currentState = 2;
            mainUI(buttons, currentPage, maxPage,1,1);
            break;

        case 7:
            currentState = 1;
            mainUI(buttons, currentPage, maxPage,0,0);
            isopen = 0;
            positionKey = 0;
            key = 0;
            str[positionKey] = '\0';
            break;

        case 8:
            currentState = 2;
            mainUI(buttons, currentPage, maxPage,1,1);
            isopen = 0;
            positionKey = 0;
            key = 0;
            str[positionKey] = '\0';
            number = 0;

            break;
        case 9:
            currentState = 2;
            mainUI(buttons, currentPage, maxPage,1,2);
            isopen = 0;
            positionKey = 0;
            key = 0;
            str[positionKey] = '\0';
            number = 0;
            break;

        case 12:
            currentState = 1;
            mainUI(buttons, currentPage, maxPage,0,0);
            break;


    }
}

void KeyboardButtons(int x){

    switch(x){
        case 0:
            keyboardy--;
            if(keyboardy <= -1){
                keyboardy = 3;
            }
            break;
        case 1:
            keyboardy++;
            if(keyboardy >= 4){
                keyboardy = 0;
            }
            break;
        case 2:
            keyboard++;
            if(keyboard >= 3){
                keyboard = 0;
            }
            break;
        case 3:
            keyboard--;
            if(keyboard <= -1){
                keyboard = 2;
            }
            break;
    }

    key = keyboard + (keyboardy * 3);
    showKeyboard(key);

}

void MenuButtonsSlot(int x){

    switch(x){
        case 2:
            slot++;
            if(slot == maxSlot + 1)
                slot = 0;
            break;
        case 3:
            slot--;
            if(slot == -1)
                slot = maxSlot;
            break;  
    }

    selectSlotMenu(slot);

}

void ConfirmButton(){
    long int modifiers[17] = {
                0x00000000,
                0x00000001,
                0x80000001,
                0x00000002,
                0x80000002,
                0x00000004,
                0x80000004,
                0x00000008,
                0x80000008,
                0x00000010,
                0x80000010,
                0x00000040,
                0x80000040,
                0x00000080,
                0x80000080,
                0x00000100,
                0x80000100
            };

    switch(currentState){
        case 0:
            if(setFile(slot)){
                setPages();
                currentState++;
                mainUI(buttons, currentPage, maxPage,0,0);
            }
            else{
                currentState = -1;
                errorScreen();
            }
            break;
        case 1:
            //showKeyboard(0);
            itemBox = 1;
            mainUI(buttons, currentPage, maxPage,1,1);
            currentState++;
            break;
        case 2:
            if(itemBox == 1){
                currentState = 8;
                keyboard = 0;
                keyboardy = 0;
                KeyboardScreen();
                isopen = 1;
            }
            if(itemBox == 2){
                itemBox = 1;
                Show_DropDownMenu(1);
                currentState++;
            }
            break;

        case 3:
            if(itemBox == 1){
                Show_DropDownMenuMod(0);
                drop = 0;
                currentState++;
            }
            else if(itemBox == 2){
                currentState = 9;
                keyboard = 0;
                keyboardy = 0;
                KeyboardScreen();
                isopen = 1;
            }
            break;
        case 4:
            
            new_modNames[currentItem] = modifiers[drop];
            currentState = 2;
            mainUI(buttons, currentPage, maxPage,1,1);
            break;

        case 7:  
            KeyboardLogic();
            if(key == 11){
                rupeeValue = number;
                currentState = 1;
                mainUI(buttons, currentPage, maxPage,0,0);
                isopen = 0;
                positionKey = 0;
                key = 0;
                str[positionKey] = '\0';

            }
            
            break;

        case 8:
            KeyboardLogic();
            if(key == 11){
                newQuantItems[currentItem] = number;
                currentState = 2;
                mainUI(buttons, currentPage, maxPage,1,1);
                isopen = 0;
                positionKey = 0;
                key = 0;
                str[positionKey] = '\0';

            }
            
            break;

        case 9:
            KeyboardLogic();
            if(key == 11){
                new_quantMod[currentItem] = number;
                currentState = 2;
                mainUI(buttons, currentPage, maxPage,1,2);
                isopen = 0;
                positionKey = 0;
                key = 0;
                str[positionKey] = '\0';

            }
            break;

    }

}

void KeyboardLogic(){
    if(positionKey < 6){
            if(key < 9){
                str[positionKey] = key + 49;
                 positionKey++;
                str[positionKey] = '\0';
            }

            if(key == 9){
                positionKey--;
                if(positionKey <= 0){
                    positionKey = 0;
                }
                str[positionKey] = '\0';
            }

            if(key == 10){
                str[positionKey] = '0';
                 positionKey++;
                str[positionKey] = '\0';
            }
           
            char string[7];
            strcpy(string, str);
            number = atoi(string);
            printText(number);
        }

    else{
        if(key == 9){
            positionKey--;
            if(positionKey <= 0){
                positionKey = 0;
            }
            str[positionKey] = '\0';
            char string[7];
            strcpy(string, str);
            number = atoi(string);
            printText(number);
        }

    }
}

void dropMenuButtons(int x){

    switch(x){
        case 0:
            drop--;
            if(drop <= -1){
                drop = 0;
            }
            break;
        case 1:
            drop++;
            if(drop >= 17){
                drop = 16;
            }
            break;
    }

    Show_DropDownMenuMod(drop);

}

void MenuButtons(int x){
    switch(x){
        case 0:
            buttons--;
            if((buttons - 1) == -2){
                currentPage--;
                if(currentPage - 1 <= -1){
                    currentPage = maxPage;
                }
                buttons = 4;
            }
            break;
        case 1:
            buttons++;
            if((buttons + 1) == 6){
                currentPage++;
                if(currentPage >= maxPage + 1){
                    currentPage = 1;
                }
                buttons = 0;
            }
            break;
        case 2:
            currentPage++;
            if(currentPage >= maxPage + 1){
                    currentPage = 1;
                }
            break;
        case 3:
            currentPage--;
            if(currentPage - 1 <= -1){
                    currentPage = maxPage;
            }
            break;

    }
    currentItem = (5 * (currentPage - 1) + buttons);
    mainUI(buttons, currentPage, maxPage, 0, 0);
}

int main(int argc, char **argv){

    appletSetScreenShotPermission(1);
    initServices();

    while(appletMainLoop())
    {
        hidScanInput();
        
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        
        if (kDown & KEY_DUP) buttonLogic(0);
        if (kDown & KEY_DDOWN) buttonLogic(1);
        if (kDown & KEY_DRIGHT) buttonLogic(2);
        if (kDown & KEY_DLEFT) buttonLogic(3);
        if (kDown & KEY_A) ConfirmButton();

        if(currentState <= 0){
            if (kDown & KEY_PLUS) break;
        }
        if(currentState != 0){
            if (kDown & KEY_B) BackButton();
            if (kDown & KEY_Y) RupeeKey();
            if (kDown & KEY_PLUS) exitMen();
            if(currentState == 12 && kDown & KEY_A){
                writeFile();
                break;
            }
            if(currentState == 12 && kDown & KEY_X){
                break;
            }
        }

        
        
    }

    closeServices();
    return 0;

}

void exitMen(){
    currentState = 12;
    exitMenu(0);
}

void RupeeKey(){
    if(isopen == 1){
        currentState = 1;
        mainUI(buttons, currentPage, maxPage, 0, 0);
        isopen = 0;
    }
    else if(isopen == 0){
        currentState = 7;
        keyboard = 0;
        keyboardy = 0;
        KeyboardScreen();
        isopen = 1;
    }
}

void closeServices(){
    fclose(fp);
    unmountSaveData();
    fsdevUnmountDevice("save");
    TTF_CloseFont(Arial);
    TTF_Quit();
    romfsExit();
    SDL_Quit();

}