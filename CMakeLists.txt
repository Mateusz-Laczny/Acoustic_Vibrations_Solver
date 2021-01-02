cmake_minimum_required(VERSION 3.17)
project(Acoustic_Vibrations_Solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(Acoustic_Vibrations_Solver main.cpp main_calculations.cpp Functions/BSplineFunction.cpp Functions/BSplineFunction.h main_calculations.h Functions/Function.h Functions/BSplineDerivative.cpp Functions/BSplineDerivative.h Functions/FunctionProduct.cpp Functions/FunctionProduct.h Functions/BoundedFunction.cpp Functions/BoundedFunction.h Functions/SineFunction.cpp Functions/SineFunction.h function_util.cpp function_util.h Functions/FunctionCombination.cpp Functions/FunctionCombination.h)