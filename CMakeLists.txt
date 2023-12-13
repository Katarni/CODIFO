cmake_minimum_required(VERSION 3.27)
project(Construction_Minimal_Disjunctive_Normal_Form)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Construction_Minimal_Disjunctive_Normal_Form src/main.cpp
        src/Constructor.cpp
        src/Constructor.h
        src/App.cpp
        src/App.h
        src/header.h)
target_link_libraries(Construction_Minimal_Disjunctive_Normal_Form
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

