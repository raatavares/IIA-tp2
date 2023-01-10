cmake_minimum_required(VERSION 3.23)
project(IIA_tp2_H C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(IIA_tp2_TrepaColinas
        TrepaColinas/main.c
        TrepaColinas/main.h
        TrepaColinas/algoritmo.c
        TrepaColinas/algoritmo.h
        TrepaColinas/utils.c
        TrepaColinas/utils.h
        TrepaColinas/funcao.c
        TrepaColinas/funcao.h
        TrepaColinas/common.c
        TrepaColinas/common.h)


add_executable(IIA_tp2_MetodoEvolutivo
        MetodoEvolutivo/main.c
        MetodoEvolutivo/main.h
        MetodoEvolutivo/metodoEvolutivo.c
        MetodoEvolutivo/metodoEvolutivo.h
        MetodoEvolutivo/common.c
        MetodoEvolutivo/common.h)

add_executable(IIA_tp2_MetodoHibrido
        MetodoHibrido/main.c
        MetodoHibrido/main.h
        MetodoHibrido/common.c
        MetodoHibrido/common.h
        MetodoHibrido/metodoHibrido.c
        MetodoHibrido/metodoHibrido.h)
