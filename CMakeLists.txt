cmake_minimum_required(VERSION 3.5)

project(HelloWord VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

list(APPEND CMAKE_PREFIX_PATH "/Users/oleksand.shcherbinin/Qt/6.7.0/macos/lib/cmake")

find_package(QT
        NAMES Qt6
        REQUIRED COMPONENTS
        Core5Compat
        Core
        Widgets
        LinguistTools
)
find_package(Qt${QT_VERSION_MAJOR}
        REQUIRED COMPONENTS
        Core5Compat
        Core
        Widgets
        LinguistTools
)

add_executable(HelloWord
        src/main.cpp
        src/Calculator.h
)

target_link_libraries(HelloWord PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Core5Compat
        Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(HelloWord PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
