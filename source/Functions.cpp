#include "ProjetImage.hpp"

/* Ne marche pas */
int area(Image & img){
  int count = 0;
  for (Image::ConstIterator it = img.begin(); it < img.end(); ++it){
    if (img(*it) > 0){
      count++;
    }
  }
  return count;
}

int perimeter(Image & img);
