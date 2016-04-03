#ifndef FUNCTIONS_HEADER
#define FUNCTIONS_HEADER

#include "ProjetImage.hpp"



int area(Image& img);

int perimeter(Image& img);

int compo_connexes(Image& img, int val, int min_item);

int holes(Image& img, int min_item);

#endif
