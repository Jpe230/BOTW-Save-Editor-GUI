#ifndef _BOTW_BACKEND_H_
#define _BOTW_BACKEND_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>



char itemName[60][40];
long int quantItems[60];
long int newQuantItems[60];
int numberOfItems;

long int rupeeValue;
long int rupees;

int rupID[7];
int itemsID[7];
int itemsQuant[7];
int header[7];
char versionArray[7][5];

int FLAGS_WEAPON[7];
int FLAGSV_WEAPON[7];
int FLAGS_BOW[7];
int FLAGSV_BOW[7];
int FLAGS_SHIELD[7];
int FLAGSV_SHIELD[7];

int numberOfWeapons;
int numberOfBows;
int numberOfShields;

long int quantMod[60];
long int new_quantMod[60];
long int modNames[60];
long int new_modNames[60];


int maxArrows;
int version;

FILE *fp;

int setFile();
void getData();
void writeFile();

#endif
