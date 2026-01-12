cmake_minimum_required(VERSION 4.1)
project(FCC C)

set(CMAKE_C_STANDARD 11)

include_directories(Headers)

add_executable(FCC
        Functions/AdjustQuadrant.c
        Functions/AdjustTgt.c
        Functions/airDensity.c
        Functions/ChargeFinder.c
        Functions/CusaTan.c
        Functions/DeflectionUpdate.c
        Functions/IntegrationLoop.c
        Functions/MaxRange.c
        Functions/PrintAllSolutions.c
        Functions/PrintSolutions.c
        Functions/QuadrantUpdate.c
        Functions/SheafSolver.c
        Functions/SolutionSolver.c
        Functions/VectorDir.c
        Functions/VectorDistance.c
        Headers/AdjustQuadrant.h
        Headers/AdjustTgt.h
        Headers/airDensity.h
        Headers/ChargeFinder.h
        Headers/Conversions.h
        Headers/CusaTan.h
        Headers/DeflectionUpdate.h
        Headers/IntegrationLoop.h
        Headers/mainInclude.h
        Headers/MaxRange.h
        Headers/PrintAllSolutions.h
        Headers/PrintSolutions.h
        Headers/QuadrantUpdate.h
        Headers/SheafSolver.h
        Headers/SolutionSolver.h
        Headers/structs.h
        Headers/VectorDir.h
        Headers/VectorDistance.h
        main.c
        Functions/SheafSolve_Open.c
        Headers/SheafSolve_Open.h
        Functions/SheafSolve_Linear.c
        Headers/SheafSolve_Linear.h
        Functions/SheafSolve_Rectangular.c
        Headers/SheafSolve_Rectangular.h
        Functions/SheafSolve_Irregular.c
        Headers/SheafSolve_Irregular.h)
