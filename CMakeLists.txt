cmake_minimum_required(VERSION 3.17)
project(Acoustic_Vibrations_Solver)

set(CMAKE_CXX_STANDARD 14)

add_executable(Acoustic_Vibrations_Solver main.cpp function_util.cpp BSplineFunction.cpp BSplineFunction.h function_util.h Function.h BSplineDerivative.cpp BSplineDerivative.h FunctionProduct.cpp FunctionProduct.h BoundedFunction.cpp BoundedFunction.h SineFunction.cpp SineFunction.h)