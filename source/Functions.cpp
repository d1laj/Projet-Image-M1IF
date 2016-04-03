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

int compo_connexes(Image & img, int val, int min_item){

  queue<Point> Q;

  int compo = 0;
  for (auto const &it : img.domain()){
    //cerr << " " << img(it);
    int count = 0;
    bool pass = false;
    if (img(it) == val){
      Q.push(it);
      compo++;
      pass = true;
    }

    while(Q.size() > 0){
      Point p = Q.front();
      Q.pop();
      if (img(p) == val){
        count++;
        img.setValue(p, -1);
        for (int i= -1; i <= 1; i++){
          for (int j= -1; j <= 1; j++){
            if (i != 0 && j != 0) continue;
            Point v = Point(p[0] + i, p[1] + j);
            if (img.domain().isInside(v) && img(v) == val){
              Q.push(v);
            }
          }
        }
      }
    }

    if (count < min_item && pass){
      compo--;
    }
  }

  cerr << endl;

  for (auto const &it : img.domain()){
    if (img(it) == -1){
      img.setValue(it, val);
    }
  }

  return compo;
}

int holes(Image & img, int min_item){

    queue<Point> Q;

    int val =0;
    int compo = 0;
    for (auto const &it : img.domain()){
      //cerr << " " << img(it);
      int count = 0;
      bool bord = false;
      bool pass = false;
      if (img(it) == val){
        Q.push(it);
        compo++;
        pass = true;
      }

      while(Q.size() > 0){
        Point p = Q.front();
        Q.pop();
        if (img(p) == val){
          count++;
          img.setValue(p, -1);
          for (int i= -1; i <= 1; i++){
            for (int j= -1; j <= 1; j++){
              if (i != 0 && j != 0) continue;
              Point v = Point(p[0] + i, p[1] + j);
              if (img.domain().isInside(v)){
                if (img(v) == val){
                  Q.push(v);
                }
              }
              else{
                bord = true;
              }
            }
          }
        }
      }

      if ((pass && count < min_item) || bord){
        compo--;
      }
    }

    cerr << endl;

    for (auto const &it : img.domain()){
      if (img(it) == -1){
        img.setValue(it, val);
      }
    }

    return compo;
}
