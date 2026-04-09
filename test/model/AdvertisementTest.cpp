#include "AdvertisementTest.h"
#include "../../model/Advertisement.h"
#include <fstream>

std::string AdvertisementTest::identify() const {
    return "ad_test";
}

TEST_F(AdvertisementTest, LoadFindsAudioFiles) {
    createFile("ad1.mp3");
    createFile("ad2.wav");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, LoadIgnoresNonAudioFiles) {
    createFile("readme.txt");
    createFile("image.png");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, LoadEmptyDirectory) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, LoadNonExistentDirectory) {
    Advertisement ad("/nonexistent/path", dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, InterruptStartsPlayback) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, InterruptReturnsTrueWithAds) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptReturnsFalseWhenNoAds) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsTrueAfterInterrupt) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseWithoutInterrupt) {
    Advertisement ad(test_directory_, dice_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseOnSecondCall) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, InterruptAfterConcludeWorks) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, LoadMixedFiles) {
    createFile("ad1.mp3");
    createFile("readme.txt");
    createFile("ad2.wav");
    createFile("image.jpg");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptPlaysFromLoadedAds) {
    createFile("only_ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, MultipleInterruptsAllStart) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    while (!ad.interrupt(listener_)) {}
    ad.conclude(listener_);
    while (!ad.interrupt(listener_)) {}
    EXPECT_TRUE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, ConcludeWithoutLoadReturnsFalse) {
    Advertisement ad(test_directory_, dice_);
    EXPECT_FALSE(ad.conclude(listener_));
}

TEST_F(AdvertisementTest, LoadMultipleMp3Files) {
    for (int i = 0; i < 8; i++) {
        createFile("ad" + std::to_string(i) + ".mp3");
    }
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptDoesNotStartWhenEmpty) {
    Advertisement ad(test_directory_, dice_);
    ad.load();
    ad.interrupt(listener_);
    EXPECT_FALSE(listener_.wasStarted());
}

TEST_F(AdvertisementTest, LoadWavFiles) {
    createFile("sound.wav");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    bool interrupted = false;
    for (int i = 0; i < 100 && !interrupted; i++) {
        interrupted = ad.interrupt(listener_);
        if (interrupted) ad.conclude(listener_);
    }
    EXPECT_TRUE(interrupted);
}

TEST_F(AdvertisementTest, InterruptProducesVariation) {
    createFile("ad.mp3");
    Advertisement ad(test_directory_, dice_);
    ad.load();
    int trueCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (ad.interrupt(listener_)) {
            trueCount++;
            ad.conclude(listener_);
        }
    }
    EXPECT_GT(trueCount, 0);
    EXPECT_LT(trueCount, 1000);
}