cmake_minimum_required(VERSION 3.20)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab2 main.cpp LongValue.h SchonhageStrassenMultiplication.cpp SchonhageStrassenMultiplication.h
        Multiplication.h BasicMultiplication.cpp BasicMultiplication.h ToomCookMultiplication.h
        ToomCookMultiplication.cpp KaratsubaMultiplication.h KaratsubaMultiplication.cpp PrimeTest.h LehmerPrimeTest.h
        LehmerPrimeTest.cpp LongValue.cpp)
