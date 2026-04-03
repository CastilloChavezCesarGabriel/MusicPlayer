#include "AdvertisementTest.h"
#include <fstream>

void AdvertisementTest::SetUp() {
    testDir = std::filesystem::temp_directory_path().string() + "/ad_test";
    std::filesystem::create_directories(testDir);
}

void AdvertisementTest::TearDown() {
    std::filesystem::remove_all(testDir);
}

void AdvertisementTest::createAdFile(const std::string& name) {
    std::ofstream(testDir + "/" + name).close();
}

TEST_F(AdvertisementTest, LoadFindsAudioFiles) {
    createAdFile("ad1.mp3");
    createAdFile("ad2.wav");
    Advertisement ad(testDir);
    ad.load();
    EXPECT_TRUE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, LoadIgnoresNonAudioFiles) {
    createAdFile("readme.txt");
    createAdFile("image.png");
    Advertisement ad(testDir);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, LoadEmptyDirectory) {
    Advertisement ad(testDir);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, LoadNonExistentDirectory) {
    Advertisement ad("/nonexistent/path");
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, InterruptStartsPlayback) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    EXPECT_TRUE(listener.wasStarted());
}

TEST_F(AdvertisementTest, InterruptReturnsTrueWhenAdsExist) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    EXPECT_TRUE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, InterruptReturnsFalseWhenNoAds) {
    Advertisement ad(testDir);
    ad.load();
    EXPECT_FALSE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, ConcludeReturnsTrueAfterInterrupt) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    EXPECT_TRUE(ad.conclude());
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseWithoutInterrupt) {
    Advertisement ad(testDir);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, ConcludeReturnsFalseOnSecondCall) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    ad.conclude();
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, InterruptAfterConcludeWorks) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    ad.conclude();
    EXPECT_TRUE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, ScheduleReturnsBool) {
    bool result = Advertisement::schedule();
    EXPECT_TRUE(result == true || result == false);
}

TEST_F(AdvertisementTest, ScheduleProducesVariation) {
    int trueCount = 0;
    for (int i = 0; i < 1000; i++) {
        if (Advertisement::schedule()) trueCount++;
    }
    EXPECT_GT(trueCount, 0);
    EXPECT_LT(trueCount, 1000);
}

TEST_F(AdvertisementTest, LoadMixedFiles) {
    createAdFile("ad1.mp3");
    createAdFile("readme.txt");
    createAdFile("ad2.wav");
    createAdFile("image.jpg");
    Advertisement ad(testDir);
    ad.load();
    EXPECT_TRUE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, InterruptPlaysFromLoadedAds) {
    createAdFile("only_ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    EXPECT_TRUE(listener.wasStarted());
}

TEST_F(AdvertisementTest, MultipleInterruptsAllStart) {
    createAdFile("ad.mp3");
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    ad.conclude();
    ad.interrupt(listener);
    EXPECT_TRUE(listener.wasStarted());
}

TEST_F(AdvertisementTest, ConcludeWithoutLoadReturnsFalse) {
    Advertisement ad(testDir);
    EXPECT_FALSE(ad.conclude());
}

TEST_F(AdvertisementTest, LoadMultipleMp3Files) {
    for (int i = 0; i < 8; i++) {
        createAdFile("ad" + std::to_string(i) + ".mp3");
    }
    Advertisement ad(testDir);
    ad.load();
    EXPECT_TRUE(ad.interrupt(listener));
}

TEST_F(AdvertisementTest, InterruptDoesNotStartWhenEmpty) {
    Advertisement ad(testDir);
    ad.load();
    ad.interrupt(listener);
    EXPECT_FALSE(listener.wasStarted());
}

TEST_F(AdvertisementTest, LoadWavFiles) {
    createAdFile("sound.wav");
    Advertisement ad(testDir);
    ad.load();
    EXPECT_TRUE(ad.interrupt(listener));
}
