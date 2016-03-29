##################
Getting libraries:
##################
apt-get install libarmadillo-dev

###############
Install mlpack:
###############:
git clone https://github.com/mlpack/mlpack.git
cd mlpack
mkdir build
cd build
cmake ..
make install
