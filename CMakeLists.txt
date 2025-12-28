cmake_minimum_required(VERSION 4.0)
project(EduScore C)


set(CMAKE_C_STANDARD 23)

add_executable(EduScore main.c
        student.h
        student.c)
