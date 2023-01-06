cmake_minimum_required(VERSION 3.23)
project(IIA_tp2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(IIA_tp2
        main.c
        main.h
        TrepaColinas/algoritmo.c
        TrepaColinas/algoritmo.h
        TrepaColinas/utils.c
        TrepaColinas/utils.h
        TrepaColinas/funcao.c
        TrepaColinas/funcao.h)
