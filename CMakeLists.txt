cmake_minimum_required(VERSION 3.31)
project(NewMusicPlayer)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(NewMusicPlayer main.cpp
        model/Song.cpp
        model/Song.h
        model/IPlaylistVisitor.h
        model/SortingAlgorithm.h
        model/ShellSort.cpp
        model/ShellSort.h
        model/QuickSort.cpp
        model/QuickSort.h
        model/Playlist.cpp
        model/Playlist.h
        model/IPlaybackListener.h
        model/Advertisement.cpp
        model/Advertisement.h
        model/MusicLibrary.cpp
        model/MusicLibrary.h
        model/Channel.cpp
        model/Channel.h
        model/PlaybackNotifier.cpp
        model/PlaybackNotifier.h
        model/Model.cpp
        model/Model.h
        view/IPlaylistPanel.h
        view/IControlPanel.h
        view/INotification.h
        view/IPlayerView.h
        view/IPlaybackControl.h
        view/ILibraryControl.h
        view/IDisplayControl.h
        view/IPlayerListener.h
        view/IAudioPlayer.h
        controller/PlaylistRenderer.cpp
        controller/PlaylistRenderer.h
        controller/Controller.cpp
        controller/Controller.h
        adapters/qt/QtPlaybackPanel.cpp
        adapters/qt/QtPlaybackPanel.h
        adapters/qt/QtVolumePanel.cpp
        adapters/qt/QtVolumePanel.h
        adapters/qt/QtToolbar.cpp
        adapters/qt/QtToolbar.h
        adapters/qt/QtProgressPanel.cpp
        adapters/qt/QtProgressPanel.h
        adapters/qt/QtSortHeader.cpp
        adapters/qt/QtSortHeader.h
        adapters/qt/QtPlaylistDisplay.cpp
        adapters/qt/QtPlaylistDisplay.h
        adapters/qt/QtAudioEngine.cpp
        adapters/qt/QtAudioEngine.h
        adapters/qt/QtViewFactory.cpp
        adapters/qt/QtViewFactory.h
        adapters/qt/QtStyler.cpp
        adapters/qt/QtStyler.h
        adapters/qt/QtView.cpp
        adapters/qt/QtView.h
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
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(NewMusicPlayerTests
        test/MockPlaybackListener.cpp
        test/MockPlaybackListener.h
        test/TestPlaylistVisitor.cpp
        test/TestPlaylistVisitor.h
        test/ModelTestFixture.cpp
        test/ModelTestFixture.h
        test/DirectoryTestFixture.cpp
        test/DirectoryTestFixture.h
        test/model/SongTest.cpp
        test/model/PlaylistTest.cpp
        test/model/AdvertisementTest.cpp
        test/model/MusicLibraryTest.cpp
        test/model/SortingTest.cpp
        test/model/ModelTest.cpp
        test/RegressionTest.cpp
        test/use_cases/PlaySongUseCaseTest.cpp
        test/use_cases/PlaySongUseCaseTest.h
        test/use_cases/SortPlaylistUseCaseTest.cpp
        test/use_cases/SortPlaylistUseCaseTest.h
        test/use_cases/SearchSongUseCaseTest.cpp
        test/use_cases/SearchSongUseCaseTest.h
        test/use_cases/AddSongUseCaseTest.cpp
        test/use_cases/AddSongUseCaseTest.h
        test/use_cases/RemoveSongUseCaseTest.cpp
        test/use_cases/RemoveSongUseCaseTest.h
        test/use_cases/NavigatePlaylistUseCaseTest.cpp
        test/use_cases/NavigatePlaylistUseCaseTest.h
        model/Song.cpp
        model/Song.h
        model/IPlaylistVisitor.h
        model/IPlaybackListener.h
        model/SortingAlgorithm.h
        model/ShellSort.cpp
        model/ShellSort.h
        model/QuickSort.cpp
        model/QuickSort.h
        model/Playlist.cpp
        model/Playlist.h
        model/Advertisement.cpp
        model/Advertisement.h
        model/MusicLibrary.cpp
        model/MusicLibrary.h
        model/Channel.cpp
        model/Channel.h
        model/PlaybackNotifier.cpp
        model/PlaybackNotifier.h
        model/Model.cpp
        model/Model.h
)

target_link_libraries(NewMusicPlayerTests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(NewMusicPlayerTests)
