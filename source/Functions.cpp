#include "Functions.hpp"

/* Ne marche pas */
int area(Image& img){
  int count = 0;
  Image::ConstIterator it;	
  for (it = img.begin(); it < img.end(); ++it){
    if (img(*it) > 0){
      count++;
    }
  }
  return count;
}

int perimeter(Image& img);
