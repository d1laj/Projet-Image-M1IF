#include "ProjetImage.hpp"
#include "Functions.hpp"
using namespace std;


int main(int argc, char** argv){
  if (argc != 4){
    fprintf(stderr, "Usage: ./ProjetImage directoryNameTrainSet directoryNameTestSet classes.csv\n");
    exit(EXIT_FAILURE);
  }

  string directoryTrain = argv[1];

  /* We get the different classes */
  Classes classes;
  get_classes(argv[3], classes);

  //int nbClasses = classes.size();

  cerr << "Training started" << endl;
  Matrix trainMat;
  arma::vec trainAnswers;
  trainMat = create_features(argv[1], trainAnswers, classes);
  cerr << "Dim : rows = " << trainMat.n_rows << " cols = " << trainMat.n_cols << endl;
  cerr << "Dim : rows = " << trainAnswers.n_rows << " cols = " << trainAnswers.n_cols << endl;
  //Matrix testMat = create_features(argv[2], classes);

  /* Learning */
  LinearRegression lr(trainMat,trainAnswers);
  cerr << "prout" << endl;
  arma::vec parameters = lr.Parameters();
  cerr << "prout" << endl;

  arma::vec predictions(180);;
  lr.Predict(trainMat,predictions);

  for (int i = 0; i < predictions.size(); i++){
    cerr << "resultat attendu :" << trainAnswers[i] << " resultat obtenu" << predictions[i] << endl;
  }

  for (int i = 0; i < predictions.size(); i++){
    cerr << "resultat attendu :" << trainAnswers[i] << " valeur : " << trainMat[0,i] << endl;
  }
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
  }

}

Matrix create_features(string directory, arma::vec & vect, Classes & classes){
  ifstream fin;
  string filepath;
  DIR *dp;
  struct dirent *dirp;
  struct stat filestat;

  cerr << "\tOpening of the directory: " << directory << endl;

  // We open the specified directory
  dp = opendir( directory.c_str() );

  // Error in the opening
  if (dp == NULL) {
    cout << "Error(" << errno << ") opening " << directory << endl;
    exit(EXIT_FAILURE);
  }
  cerr << "\tDirectory opened" << endl;
  Matrix matrix= arma::mat();

  while ((dirp = readdir( dp ))) {
    filepath = directory + "/" + dirp->d_name;
    string filename = dirp->d_name;

    // If the file is a directory (or is in some way invalid) we'll skip it
    if (stat( filepath.c_str(), &filestat )) continue;
    if (S_ISDIR( filestat.st_mode ))         continue;

    // We check if the file is correct
    size_t pos = filename.find_last_of(".");
    string ext = filename.substr(pos);
    // Test if the string is a pgm file.

    if (ext.compare(".pgm"))  continue;

    cerr << "\tChecking pgm file: " << filepath << endl;
    pos = filename.find_last_of("-");
    string cla = filename.substr(0, pos);
    // We add a row to the answer vector
    cerr << "\tma classe : \"" << cla << "\"" << endl;
    vect.insert_rows(vect.n_rows, 1);
    // We test if the file name infer it's class.
    // This is used to identify the classes in the train set.
    if (classes.count(cla) > 0){
      // We add the class number to the answer vector
      vect(vect.n_rows -1) = classes[cla];
    }
    else{
      // No class number
      vect(vect.n_rows -1) = 0;
    }
    // Then we get the image
    Image image = PGMReader<Image>::importPGM(filepath);
    // We extract the features
    cerr << filepath << " has area "; // TODO
    Feature col= feature_extract(image);
    // we add the features to the matrix
    matrix.insert_cols(matrix.n_cols, col);
  }

  closedir( dp );
  cerr << "\tEnd of the feature extraction" << endl;
  return matrix;
}

Matrix create_features(string directory, Classes & classes){
  arma::vec vect;
  return create_features(directory, vect, classes);
}

Feature feature_extract(Image image){
  cerr << area(image) << endl;
  Feature feature = arma::colvec(1);
  /* cerr << "\tcompo connexes : " << compo_connexes(image) << endl; */
  feature(0)= ((double) perimeter(image)*perimeter(image))/((double) area(image));
  return feature;
}
