#include "ProjetImage.hpp"
#include "Functions.hpp"
using namespace std;

void usage(){
    fprintf(stderr, "Usage: ./ProjetImage -train directoryNameTrainSet classes.csv\n");
    fprintf(stderr, "Usage: ./ProjetImage -test file.pgm\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
    if (argc < 3){
        usage();
    }

    ofstream myfile;

    if (argv[1] == "-train"){
        string directoryTrain = argv[2];

        /* We get the different classes */
        Classes classes;
        get_classes(argv[3], classes);

        cerr << "Training started" << endl;
        Matrix trainMat;
        arma::vec trainAnswers;
        trainMat = create_features(argv[1], trainAnswers, classes);

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
    }
    else if (argv[1] == "-test"){
        if (argc != 2){
            usage();
        }

        string filename = argv[2];
        // We check if the file is correct
        size_t pos = filename.find_last_of(".");
        if (pos > filename.size()) continue;

        string ext = filename.substr(pos);
        // Test if the string is a pgm file.
        if (ext.compare(".pgm")){
            fprint(stderr, "Error: Not a pgm file !");
        }

        // We get the image
        Image image = PGMReader<Image>::importPGM(filepath);
        // We extract the features
        Feature col= feature_extract(image);

        myfile.open("test.csv");
        myfile << col(0) << "," << col(1) << "," << col(2) << "," << col(3) << endl;
        myfile.close();
    }
    else{
        usage();
    }

    /*
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
    */
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
        cerr << "\tChecking pgm file: " << filepath << "[" << counter << "]"<< endl;
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
        Feature col= feature_extract(image);
        // we add the features to the matrix
        matrix.insert_cols(matrix.n_cols, col);
    }

    closedir( dp );
    //cerr << "\tEnd of the feature extraction" << endl;
    return matrix;
}

Feature feature_extract(Image image){
    // Create the feature vector
    Feature feature = arma::colvec(4);
    // We make a preprossesing
    preprossesing(image);
    // We get the features
    feature(0)= ((double) perimeter(image)*perimeter(image))/((double) area(image));
    feature(1) = compo_connexes(image, 255, 10);
    feature(2) = holes(image, 10);
    feature(3) = ratio_longueur_largeur(image);
    return feature;
}
