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

int compo_connexes(Image& img){
  int count = 0;
  for (auto const &it : img.domain()){
    if (img(it) > 0){
      count++;
      img.setValue(it, count);
    }
  }

  for (auto const &it : img.domain()){
    if (img(it) > 0){
      for (int i= -1; i <= 1; i++){
        for (int j= -1; j <= 1; j++){
          if (img.domain().isInside(it)){

          }
        }
      }
    }
  }
  return 0;
}
