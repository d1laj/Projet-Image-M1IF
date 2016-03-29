#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/readers/PGMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

using namespace std;

int main(int argc, char** argv){
	if (argc != 4){
		fprintf(stderr, "Usage: ./ProjetImage directoryNameTrainSet directoryNameTestSet classes.csv\n");
		exit(EXIT_FAILURE);
	}

	string directoryTrain = argv[1];

	/* We get the different classes */
  map<string, int> classes;

	ifstream file ( argv[3] );
  int i = 0;
	string key;
	while ( file.good() ){
		   getline( file, key, ',' );
       ++i;
       if (key.size() >0 && key[0] == '\n'){
         key.erase(0, 1);
       }
       if (key.size() > 0){
         classes[key]= i;
       }
	}

  printf("Classes :\n");
  for(auto const &it : classes) {
    cout << "classe: " << it.first << " | ind: " << it.second << "\n";
  }

	/* Pour chaque fichier dans le dossier */
		/* Feature extraction */

	/* Learning */


}
