cmake_minimum_required(VERSION 3.8)
project(MathUsingCPP)

set(CMAKE_CXX_STANDARD 14)

set(EXCEPTIONS
        # Not Implemented
        Exceptions/NotImplementedError.h
        # Illegal Access
        Exceptions/IllegalAccessException.h
        )

set(SOURCE_FILES
        # Expression
        Expression.h
        # Base Expression
        BaseExpression.h
        # Binary Expressions
        BinaryExpression.cpp BinaryExpression.h

        main.cpp)

add_executable(MathUsingCPP ${SOURCE_FILES} ${EXCEPTIONS})