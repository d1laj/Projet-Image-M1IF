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
		  if((img.domain().isInside(test1)&&img(test1)==0)
        ||(img.domain().isInside(test2)&&img(test2)==0)
        ||(img.domain().isInside(test3)&&img(test3)==0)
        ||(img.domain().isInside(test4)&&img(test4)==0)){
          count++;
			}
	  }
  }
  return count;
}

void comp_connexes_add_neighboors(Point it, queue<Point> & Q, Image & img, int val){
  for (int i= -1; i <= 1; i++){
    for (int j= -1; j <= 1; j++){
      if (i != 0 && j != 0) continue;
      Point p = Point(it[0] + i, it[1] + j);
      if (img.domain().isInside(p) && img(p) == val){
        Q.push(p);
      }
    }
  }
}

int compo_connexes(Image & img, int val){

  queue<Point> Q;

  int count = 2;
  for (auto const &it : img.domain()){
    if (img(it) == val){
      img.setValue(it, count);
      comp_connexes_add_neighboors(it, Q, img, val);

      while(!Q.size() > 0){
        Point p = Q.front();
        Q.pop();
        if (img(it) == val){
          img.setValue(it, count);
          comp_connexes_add_neighboors(it, Q, img, val);
        }
      }

      count++;
    }
  }

  count--;

  for (auto const &it : img.domain()){
    if (img(it) == val){
      img.setValue(it, val);
    }
  }

  return count;
}
