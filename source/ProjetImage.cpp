#include "ProjetImage.hpp"

using namespace std;

int main(int argc, char** argv){
  if (argc != 4){
    fprintf(stderr, "Usage: ./ProjetImage directoryNameTrainSet directoryNameTestSet classes.csv\n");
    exit(EXIT_FAILURE);
  }

  string directoryTrain = argv[1];

  /* We get the different classes */
  map<string, int> classes;
  get_classes(argv[3], classes);

  int nbClasses = classes.size();



  /* Pour chaque fichier dans le dossier */
    /* Feature extraction */

  /* Learning */


}

void get_classes(char* filename, map<string, int> & classes){
  // Open the file
  ifstream file ( filename );
  int i = 0;
  string key;

  while ( file.good() ){
    // Get a line
    getline( file, key, ',' );
    ++i;
    // Add the class
    if (key.size() > 0 ){
      if (key[0] == '\n'){
        key.erase(0, 1);
      }
      classes[key]= i;
    }
  }

  fprintf(stderr, "Classes :\n");
  for(auto const &it : classes) {
    cerr << "classe: " << it.first << " | ind: " << it.second << "\n";
  }

}
