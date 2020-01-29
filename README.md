# simple_benchmark_template
Simple Benchmark template

Fork from [RichardDally/MicroBenchmark](https://github.com/RichardDally/MicroBenchmark)

```
git submodule add -f https://github.com/google/googletest.git benchmark/googletest
git submodule update --init --recursive
```

Build benchmark Release and Debug
```
cd benchmark
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build .
```

Build
```
mkdir build
cd build 
cmake -G "Visual Studio 16 2019" ..
cmake --build .
```


