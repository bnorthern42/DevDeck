cmake_minimum_required(VERSION 3.14)
project(DevDeck VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_executable(DevDeck
    main.cpp
    mainwindow.h
    mainwindow.cpp
    FileHandler.h
    FileHandler.cpp
    LanguageConfigLoader.h
    LanguageConfigLoader.cpp
    BuildRunner.h
    BuildRunner.cpp
)

target_link_libraries(DevDeck Qt5::Core Qt5::Widgets)
