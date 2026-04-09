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
        model/core/Song.cpp
        model/core/Song.h
        model/core/Playlist.cpp
        model/core/Playlist.h
        model/core/FileMetadata.cpp
        model/core/FileMetadata.h
        model/library/MusicLibrary.cpp
        model/library/MusicLibrary.h
        model/playback/Channel.cpp
        model/playback/Channel.h
        model/ads/Advertisement.cpp
        model/ads/Advertisement.h
        model/ads/IAdPolicy.h
        model/ads/RandomAdPolicy.cpp
        model/ads/RandomAdPolicy.h
        model/ads/IDice.h
        model/ads/Dice.cpp
        model/ads/Dice.h
        model/repeat/RepeatMode.cpp
        model/repeat/RepeatMode.h
        model/repeat/RepeatStrategy.cpp
        model/repeat/RepeatStrategy.h
        model/repeat/NoRepeatMode.cpp
        model/repeat/NoRepeatMode.h
        model/repeat/RepeatOneMode.cpp
        model/repeat/RepeatOneMode.h
        model/repeat/RepeatAllMode.cpp
        model/repeat/RepeatAllMode.h
        model/arrangement/Arrangement.cpp
        model/arrangement/Arrangement.h
        model/arrangement/ISortingAlgorithm.h
        model/arrangement/QuickSort.cpp
        model/arrangement/QuickSort.h
        model/arrangement/ShellSort.cpp
        model/arrangement/ShellSort.h
        model/arrangement/DateSort.cpp
        model/arrangement/DateSort.h
        model/arrangement/DurationSort.cpp
        model/arrangement/DurationSort.h
        model/events/IPlaylistVisitor.h
        model/events/IPlaybackListener.h
        model/events/IPlaybackEvent.h
        model/events/IDisplayEvent.h
        model/events/ILibraryEvent.h
        model/events/PlaybackNotifier.cpp
        model/events/PlaybackNotifier.h
        model/events/PlaybackEventNotifier.cpp
        model/events/PlaybackEventNotifier.h
        model/events/DisplayEventNotifier.cpp
        model/events/DisplayEventNotifier.h
        model/events/LibraryEventNotifier.cpp
        model/events/LibraryEventNotifier.h
        model/MusicPlayer.cpp
        model/MusicPlayer.h
        view/IPlaybackControl.h
        view/ILibraryControl.h
        view/IDisplayControl.h
        view/IPlaybackView.h
        view/ILibraryView.h
        view/IDisplayView.h
        controller/PlaylistRenderer.cpp
        controller/PlaylistRenderer.h
        controller/SortMode.cpp
        controller/SortMode.h
        controller/TitleDescending.cpp
        controller/TitleDescending.h
        controller/CustomMode.cpp
        controller/CustomMode.h
        controller/SortController.cpp
        controller/SortController.h
        controller/SearchController.cpp
        controller/SearchController.h
        controller/PlaybackDispatcher.cpp
        controller/PlaybackDispatcher.h
        controller/LibraryDispatcher.cpp
        controller/LibraryDispatcher.h
        controller/DisplayDispatcher.cpp
        controller/DisplayDispatcher.h
        controller/PlaybackBridge.cpp
        controller/PlaybackBridge.h
        controller/DisplayBridge.cpp
        controller/DisplayBridge.h
        controller/LibraryBridge.cpp
        controller/LibraryBridge.h
        adapters/qt/QtLayoutUtil.cpp
        adapters/qt/QtLayoutUtil.h
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
        adapters/qt/QtSearchOverlay.cpp
        adapters/qt/QtSearchOverlay.h
        adapters/qt/QtAudioEngine.cpp
        adapters/qt/QtAudioEngine.h
        adapters/qt/QtNotification.cpp
        adapters/qt/QtNotification.h
        adapters/qt/QtDialog.cpp
        adapters/qt/QtDialog.h
        adapters/qt/QtDragDrop.cpp
        adapters/qt/QtDragDrop.h
        adapters/qt/QtViewFactory.cpp
        adapters/qt/QtViewFactory.h
        adapters/qt/QtStyler.cpp
        adapters/qt/QtStyler.h
        adapters/qt/QtPlaybackWidget.cpp
        adapters/qt/QtPlaybackWidget.h
        adapters/qt/QtLibraryWidget.cpp
        adapters/qt/QtLibraryWidget.h
        adapters/qt/QtDisplayWidget.cpp
        adapters/qt/QtDisplayWidget.h
)

target_include_directories(NewMusicPlayer PRIVATE ${CMAKE_SOURCE_DIR})

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
        test/model/FileMetadataTest.cpp
        test/model/FileMetadataTest.h
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
        model/core/Song.cpp
        model/core/Song.h
        model/core/Playlist.cpp
        model/core/Playlist.h
        model/core/FileMetadata.cpp
        model/core/FileMetadata.h
        model/library/MusicLibrary.cpp
        model/library/MusicLibrary.h
        model/playback/Channel.cpp
        model/playback/Channel.h
        model/ads/Advertisement.cpp
        model/ads/Advertisement.h
        model/ads/IAdPolicy.h
        model/ads/RandomAdPolicy.cpp
        model/ads/RandomAdPolicy.h
        model/ads/IDice.h
        model/ads/Dice.cpp
        model/ads/Dice.h
        model/repeat/RepeatMode.cpp
        model/repeat/RepeatMode.h
        model/repeat/RepeatStrategy.cpp
        model/repeat/RepeatStrategy.h
        model/repeat/NoRepeatMode.cpp
        model/repeat/NoRepeatMode.h
        model/repeat/RepeatOneMode.cpp
        model/repeat/RepeatOneMode.h
        model/repeat/RepeatAllMode.cpp
        model/repeat/RepeatAllMode.h
        model/arrangement/Arrangement.cpp
        model/arrangement/Arrangement.h
        model/arrangement/ISortingAlgorithm.h
        model/arrangement/QuickSort.cpp
        model/arrangement/QuickSort.h
        model/arrangement/ShellSort.cpp
        model/arrangement/ShellSort.h
        model/arrangement/DateSort.cpp
        model/arrangement/DateSort.h
        model/arrangement/DurationSort.cpp
        model/arrangement/DurationSort.h
        model/events/IPlaylistVisitor.h
        model/events/IPlaybackListener.h
        model/events/IPlaybackEvent.h
        model/events/IDisplayEvent.h
        model/events/ILibraryEvent.h
        model/events/PlaybackNotifier.cpp
        model/events/PlaybackNotifier.h
        model/events/PlaybackEventNotifier.cpp
        model/events/PlaybackEventNotifier.h
        model/events/DisplayEventNotifier.cpp
        model/events/DisplayEventNotifier.h
        model/events/LibraryEventNotifier.cpp
        model/events/LibraryEventNotifier.h
        model/MusicPlayer.cpp
        model/MusicPlayer.h
)

target_include_directories(NewMusicPlayerTests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(NewMusicPlayerTests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(NewMusicPlayerTests)
