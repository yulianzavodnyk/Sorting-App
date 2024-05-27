# Specify the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.27)

# Define the project name
project(First_Year_CS_Coursework)

# Set the C++ standard to C++17 and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable automatic handling of Qt's MOC (Meta-Object Compiler), RCC (Resource Compiler), and UIC (User Interface Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required Qt5 packages for the project: Core, Gui, and Widgets modules
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# Define the executable and specify the source files to be compiled
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

# Link the executable to the required Qt5 libraries
target_link_libraries(First_Year_CS_Coursework
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)