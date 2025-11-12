cmake_minimum_required(VERSION 3.10)


project(sibela)

add_executable(sibela main.c)
add_library(draw SHARED components/header.c)
add_library(utils SHARED libs/utils.c)
add_library(model SHARED model/model.c)
add_library(update SHARED update/update.c)
add_library(view SHARED views/drawView.c)
add_library(home SHARED views/homeView.c)


target_link_libraries(sibela PRIVATE draw utils model update view home ncurses)