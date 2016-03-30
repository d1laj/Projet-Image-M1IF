#ifndef PROJET_IMAGE_HEADER
#define PROJET_IMAGE_HEADER

/* Standard C++ librairies  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
/* DGtal */
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/readers/PGMReader.h>
#include <DGtal/images/imagesSetsUtils/SetFromImage.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
/* Librairies linked to data learning */
#include <armadillo>

using namespace std;

/* Look at the classes.csv file and store the classes with an index for each of them*/
void get_classes(char* filename, map<string, int> & classes);

typedef arma::mat Matrix;
typedef arma::vec Feature;

/* Create a feature matrix corrresponding to the files.*/
Matrix create_features(string directory, arma::vec & vect); // Train set
Matrix create_features(string directory); // Test Set

/* Features
  _ ration aire/perimetre
  _ nombre composante connexes
  _ nombre de "grosses" composantes connexes
  _ (trouver deux vecteurs de directions principales)
  _ symétrie ?


*/

#endif
