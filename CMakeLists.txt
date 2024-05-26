cmake_minimum_required(VERSION 3.27)
project(First_Year_CS_Coursework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(First_Year_CS_Coursework
        src/app/sorts/sorts.h
        src/app/sorts/core.cpp
        src/app/sorts/heap_sort.cpp
        src/app/sorts/quick_sort.cpp
        src/app/sorts/merge_sort.cpp
        src/app/sorts/metrics.cpp
        src/app/sorts/array.cpp
        src/app/window.h
        src/app/window.cpp
        src/app/window.ui
        src/main.cpp
)

target_link_libraries(First_Year_CS_Coursework
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)