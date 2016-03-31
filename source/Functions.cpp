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

int perimeter(Image& img){

	int count = 0;
	for (auto const &it : img.domain()){
		if (img(it)>0){
		  Point test1 =  Point(it[0]-1, it[1]);
		  Point test2 =  Point(it[0]+1, it[1]);
		  Point test3 =  Point(it[0], it[1]-1);
		  Point test4 =  Point(it[0], it[1]+1);
		  if((img.domain().isInside(test1)&&img(test1)==0)||(img.domain().isInside(test2)&&img(test2)==0)||(img.domain().isInside(test3)&&img(test3)==0)||(img.domain().isInside(test4)&&img(test4)==0)){
			  count++;
			}
	  }
  }
  return count;
}


int compo_connexes(Image & img){

  int count = 0;
  for (auto const &it : img.domain()){
    if (img(it) > 0){
      count++;
      img.setValue(it, count);
    }
  }

  bool cont = true;
  while (cont){
    cont = false;
    for (auto const &it : img.domain()){
      if (img(it) > 0){
        int min = img(it);
        for (int i= -1; i <= 1; i++){
          for (int j= -1; j <= 1; j++){
            if (i != 0 && j != 0) continue;
            Point p = Point(it[0] + i, it[1] + j);
            if (img.domain().isInside(p) && img(p) > 0){
              if (img(p) < min){
                min = img(p);
                cont = true;
              }
            }
          }
        }
        img.setValue(it, min);
      }
    }
  }


  set<int> compo;
  for (auto const &it : img.domain()){
    if (img(it) > 0){
      compo.insert(img(it));
      img.setValue(it, 1);
    }
  }

  return compo.size();

  return 0;
}
