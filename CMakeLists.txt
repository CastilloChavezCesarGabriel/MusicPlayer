cmake_minimum_required(VERSION 3.31)
project(NewMusicPlayer)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenSSL REQUIRED)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(NewMusicPlayer main.cpp
        model/Song.cpp
        model/Song.h
        model/Hash.cpp
        model/Hash.h
        model/ISorting.h
        model/SongSorting.cpp
        model/SongSorting.h
        model/Model.cpp
        model/Model.h
        view/View.cpp
        view/View.h
        controller/Controller.cpp
        controller/Controller.h
)

add_custom_target(CopyResources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:NewMusicPlayer>/resources
)

add_dependencies(NewMusicPlayer CopyResources)

target_link_libraries(NewMusicPlayer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        OpenSSL::Crypto
)

