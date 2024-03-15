комиляция выполнялась с помощью:
gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04) 

сборка выполнялась с помощью:
cmake version 3.22.1 

операционная система:
Ubuntu 22.04.3 LTS

To use the parallel execution policies with GCC you have to link to Intel TBB using
not forget to add tbb to libraries TARGET_LINK_LIBRARIES(mtfind ${Boost_LIBRARIES} tbb)


Программа собирается и компилируется с помощью CMake.

mkdir build
cd build
cmake ..
cmake --build .

получаем файл mtfind

инструкция по использованию опций командной строки
./mtfind -h 


в папке rndtxt программа для создания тестового фала
