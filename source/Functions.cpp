#include "ProjetImage.hpp"

/* Ne marche pas */
int area(Image& img){
  int count = 0;
  for (auto const &it : img.domain()){
    if (img(it) > 0){
      count++;
    }
  }
  return count;
}

int perimeter(Image& img);
