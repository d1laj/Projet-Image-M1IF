#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "ProjetImage.hpp"



int area(Image& img);

int perimeter(Image& img);

int compo_connexes(Image& img, int val, int min_item);

int holes(Image& img, int min_item);

double ratio_longueur_largeur(Image & img);

void preprossesing(Image & img);
#endif
