cmake_minimum_required(VERSION 3.5)

project(UPRE_Serial_Assistant LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Widgets SerialPort REQUIRED)

add_executable(target
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    myappico.ico
  )

target_link_libraries(target PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::SerialPort
    )
