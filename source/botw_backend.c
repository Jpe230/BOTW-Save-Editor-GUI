#include "botw_backend.h"

int rupID[7]      = {0x00e0a0, 0x00e110, 0x00e110, 0x00e678, 0x00e730, 0x00eaf8, 0x00eaf8};
int itemsID[7]    = {0x052828, 0x0528d8, 0x0528c0, 0x053890, 0x05fa48, 0x060408, 0x060408};
int itemsQuant[7] = {0x063340, 0x0633f0, 0x0633d8, 0x064550, 0x070730, 0x0711c8, 0x0711c8};
int header[7]     = {0x24e2,   0x24ee,   0x2588,   0x29c0,   0x3ef8,   0x471a,   0x471b};
int FLAGS_WEAPON[7] =  {0x050328, 0x0503d8, 0x0503c0, 0x051270, 0x05d420, 0x05dd20, 0x05dd20};
int FLAGSV_WEAPON[7] = {0x0a9ca8, 0x0a9d78, 0x0a9d58, 0x0ab8d0, 0x0c3bd8, 0x0c4c68, 0x0c4c68};
int FLAGS_BOW[7]={0x0045f0, 0x0045f8, 0x0045f8, 0x0047e8, 0x004828, 0x004990, 0x004990};
int FLAGSV_BOW[7]={0x00a8e0, 0x00a940, 0x00a940, 0x00ae08, 0x00ae90, 0x00b1e0, 0x00b1e0};
int FLAGSV_SHIELD[7]={0x063218, 0x0632c8, 0x0632b0, 0x064420, 0x070600, 0x071098, 0x071098};
int FLAGS_SHIELD[7]={0x0b5810, 0x0b58e8, 0x0b58c8, 0x0b7910, 0x0cfc70, 0x0d1038, 0x0d1038};

void writeFile(){

    if(rupeeValue != rupees){
            fseek(fp,rupID[version],SEEK_SET);
            fwrite(&rupeeValue, sizeof(long int), 1, fp);
    }

    for(int x = 0; x < numberOfItems; x++){
        if(newQuantItems[x] != quantItems[x]){
            fseek(fp, itemsQuant[version] + (8 * x),SEEK_SET);
            fwrite(&newQuantItems[x], sizeof(int), 1, fp);
        }
    }

    for(int x = 0; x<numberOfWeapons; x++){
        if(new_quantMod[x] != quantMod[x]){
            fseek(fp, FLAGSV_WEAPON[version] + (8 * x),SEEK_SET);
            fwrite(&new_quantMod[x], sizeof(int), 1, fp);
        }

        if(new_modNames[x] != modNames[x]){
            fseek(fp, FLAGS_WEAPON[version] + (8 * x),SEEK_SET);
            fwrite(&new_modNames[x], sizeof(long int), 1, fp);
        }    
    }

    for(int x = 0; x<numberOfBows; x++){
        if(new_quantMod[x + numberOfWeapons] != quantMod[x + numberOfWeapons]){
            fseek(fp, FLAGSV_BOW[version] + (8 * x),SEEK_SET);
            fwrite(&new_quantMod[x + numberOfWeapons], sizeof(int), 1, fp);
        }
        if(new_modNames[x + numberOfWeapons] != modNames[x + numberOfWeapons]){
            fseek(fp, FLAGS_BOW[version] + (8 * x),SEEK_SET);
            fwrite(&new_modNames[x + numberOfWeapons], sizeof(long int), 1, fp);
        }    
    }

    for(int x = 0; x<numberOfShields; x++){

        if(new_quantMod[x + numberOfWeapons + numberOfBows + 6] != quantMod[x + numberOfWeapons + numberOfBows + 6]){
            fseek(fp, FLAGSV_SHIELD[version] + (8 * x),SEEK_SET);
            fwrite(&new_quantMod[x + numberOfWeapons + numberOfBows + 6], sizeof(int), 1, fp);
        }
        if(new_modNames[x + numberOfWeapons + numberOfBows + 6] != modNames[x + numberOfWeapons + numberOfBows + 6]){
            fseek(fp, FLAGS_SHIELD[version] + (8 * x),SEEK_SET);
            fwrite(&new_modNames[x + numberOfWeapons + numberOfBows + 6], sizeof(int), 1, fp);
        }
    }

}

void getData(){

    int readHeader;
    
    fread(&readHeader, sizeof(int), 1, fp);
    
    for(version = 0; version<7; version++){
        
        if(readHeader == header[version]){
            break;
        }
        
    }

    fseek(fp,rupID[version],SEEK_SET);
    fread(&rupees, sizeof(long int), 1, fp);
    rupeeValue = rupees;
    int endOfItems = 0;
    
    for(int y = 0; y < 50 ;y++){
        
        int offset = (y * 128);

        for(int x = 0; x < 5; x++){
            char tmpString[5];
            
            fseek(fp, itemsID[version] + (8 * x) + offset,SEEK_SET);
            fread(&tmpString, sizeof(int), 1, fp);

            if(tmpString[strlen(tmpString) - 1] == 2){
                tmpString[strlen(tmpString) - 1] = 0;
            }

            sprintf(itemName[y] + strlen(itemName[y]),"%s", tmpString);
            
            if(strcmp(itemName[y],"Armo") == 0)
                endOfItems = 1;

            if(strcmp(tmpString,"swor")==0 || strcmp(tmpString,"word")==0 || strcmp(tmpString,"pear")==0){
                numberOfWeapons++;
            }

            if(strcmp(tmpString,"ow_0")==0){
                numberOfBows++;
            }
            
            if(strcmp(tmpString,"hiel")==0){
                numberOfShields++;
            }
        }

        if(endOfItems == 1)
            break;

        fseek(fp, itemsQuant[version] + (8 * y),SEEK_SET);
        fread(&quantItems[y], sizeof(int), 1, fp);

        newQuantItems[y] = quantItems[y];
        numberOfItems++;
    }

    int x;

    for(x = 0; x<numberOfWeapons; x++){
            
        fseek(fp, FLAGS_WEAPON[version] + (8 * x),SEEK_SET);
        fread(&modNames[x], sizeof(int), 1, fp);
        fseek(fp, FLAGSV_WEAPON[version] + (8 * x),SEEK_SET);
        fread(&quantMod[x], sizeof(int), 1, fp);
        new_modNames[x] = modNames[x];
        new_quantMod[x] = quantMod[x];
            
    }
    
    
    for(x = 0; x<numberOfBows; x++){
        fseek(fp, FLAGS_BOW[version] + (8 * x),SEEK_SET);
        fread(&modNames[x + numberOfWeapons], sizeof(int), 1, fp);
        fseek(fp, FLAGSV_BOW[version] + (8 * x),SEEK_SET);
        fread(&quantMod[x + numberOfWeapons], sizeof(int), 1, fp);
        new_modNames[x + numberOfWeapons] = modNames[x + numberOfWeapons];
        new_quantMod[x + numberOfWeapons] = quantMod[x + numberOfWeapons];
    }

    for(x = 0; x<numberOfShields; x++){
        fseek(fp, FLAGS_SHIELD[version] + (8 * x),SEEK_SET);
        fread(&modNames[x + numberOfWeapons + numberOfBows + 6], sizeof(int), 1, fp);
        fseek(fp, FLAGSV_SHIELD[version] + (8 * x),SEEK_SET);
        fread(&quantMod[x + numberOfWeapons + numberOfBows + 6], sizeof(int), 1, fp);
        new_modNames[x + numberOfWeapons + numberOfBows + 6] = modNames[x + numberOfWeapons + numberOfBows + 6];
        new_quantMod[x + numberOfWeapons + numberOfBows + 6] = quantMod[x + numberOfWeapons + numberOfBows + 6];
    }

}


int setFile(int intSlot){

	for (int x = 0; x < 60; x++){
		itemName[x][0] = 0;
		quantItems[x] = 0;
		newQuantItems[x] = 0;	
    }
    

	numberOfItems = 0; 
	rupeeValue = 0;
	rupees = 0;

    mountSaveData();

    char file_name[75];
    char header[] = "save:/";
    char footer[] = "/game_data.sav";

    snprintf(file_name, sizeof file_name, "%s%d%s", header, intSlot, footer);
    
    fp = fopen(file_name,"r+b");
    
    if( fp == NULL )
    {
        return 0;
    }


    else{
        getData(); 
        return 1; 
    }
    
}

