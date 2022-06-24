cmake_minimum_required(VERSION 3.5)

if(WebAssemblyBuild)
	if(NOT DEFINED ENV{EMSDK})
		message(FATAL_ERROR "Must have EMSDK set in environment variable to compile for Web Assembly.")
	endif()
	set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake")
endif()

project(Disconnect VERSION 0.1 LANGUAGES CXX)

if(WebAssemblyBuild)
  include(emscripten.cmake)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(include)
set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        include/mainwindow.h
        disconnect.qrc
        ui/mainwindow.ui
        controller/GameController.cpp
        generator/MoveGenerator.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Disconnect
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Disconnect APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Disconnect SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Disconnect
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Disconnect PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(Disconnect PUBLIC include)

set_target_properties(Disconnect PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Disconnect)
endif()

add_custom_target(InitializeGameboard ${CMAKE_CURRENT_SOURCE_DIR}/initialize_gameboard.py ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS ui/mainwindow.cpp)
add_dependencies(Disconnect InitializeGameboard)

add_executable(GameBoardUnitTest game/GameBoardUnitTest.cpp game/Game.cpp)

if(WebAssemblyBuild)
	link_qt_static(Disconnect)
endif()
