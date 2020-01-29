git clone https://github.com/google/benchmark.git benchmark
cd benchmark
git clone https://github.com/google/googletest.git 
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" ..
cmake --build .
cd ..
cd ..
mkdir build
cd build 
cmake -G "Visual Studio 14 2015 Win64" ..
cmake --build .
cd ..