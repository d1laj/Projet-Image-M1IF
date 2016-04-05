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
    Matrix testMat;
    arma::vec trainAnswers;
    arma::vec testAnswers;
    trainMat = create_features(argv[1], trainAnswers, classes);
    testMat = create_features(argv[2], testAnswers, classes);
    cerr << "Dim : rows = " << trainMat.n_rows << " cols = " << trainMat.n_cols << endl;
    cerr << "Dim : rows = " << testMat.n_rows << " cols = " << testMat.n_cols << endl;
    cerr << "Dim : rows = " << trainAnswers.n_rows << " cols = " << trainAnswers.n_cols << endl;
    //Matrix testMat = create_features(argv[2], classes);

    ofstream myfile;
    myfile.open("answers.csv");
    for (uint i=0; i < trainAnswers.size(); i++){
        myfile << trainAnswers(i) << "\n";
    }
    myfile.close();

    myfile.open("answers_test.csv");
    for (uint i=0; i < testAnswers.size(); i++){
        myfile << testAnswers(i) << "\n";
    }
    myfile.close();

    myfile.open("train.csv");
    for (uint i=0; i < trainAnswers.size(); i++){
        for (uint j=0; j < trainMat.n_rows; j++){
            myfile << trainMat(j, i);
            if (j == trainMat.n_rows - 1){
                myfile << "\n";
            }
            else{
                myfile << ",";
            }
        }
    }
    myfile.close();

    myfile.open("test.csv");
    for (uint i=0; i < testMat.n_cols; i++){
        for (uint j=0; j < testMat.n_rows; j++){
            myfile << testMat(j, i);
            if (j == testMat.n_rows - 1){
                myfile << "\n";
            }
            else{
                myfile << ",";
            }
        }
    }
    myfile.close();
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

    //fprintf(stderr, "Classes :\n");

}

Matrix create_features(string directory, arma::vec & vect, Classes & classes){
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

    int counter = 0;
    while ((dirp = readdir( dp ))) {
        filepath = directory + "/" + dirp->d_name;
        cerr << filepath << endl;
        string filename = dirp->d_name;

        // If the file is a directory (or is in some way invalid) we'll skip it
        if (stat( filepath.c_str(), &filestat )) continue;
        if (S_ISDIR( filestat.st_mode ))         continue;

        // We check if the file is correct
        size_t pos = filename.find_last_of(".");
        if (pos > filename.size()) continue;

        string ext = filename.substr(pos);
        // Test if the string is a pgm file.

        if (ext.compare(".pgm"))  continue;

        counter++;
        cerr << "\tChecking pgm file: " << filepath << "[" << counter << "/1050]"<< endl;
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
        //cerr << filepath << " has area "; // TODO
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
    //cerr << area(image) << endl;
    Feature feature = arma::colvec(4);
    //cerr << "\tcompo connexes : " << compo_connexes(image) << endl;
    feature(0)= ((double) perimeter(image)*perimeter(image))/((double) area(image));
    feature(1) = compo_connexes(image, 255, 10);
    feature(2) = holes(image, 10);
    feature(3) = ratio_longueur_largeur(image);
    cerr << feature(3) << endl;
    return feature;
}
