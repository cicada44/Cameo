#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include <managers/managers.hpp>

TEST(Manager, WindowManager) {
    Managers::WindowManager winManager("window");
    ASSERT_EQ(winManager.getWindowName(), "window");
    ASSERT_FALSE(winManager.isWindowCreated());
    winManager.createWindow();
    ASSERT_TRUE(winManager.isWindowCreated());
    cv::Mat blackMatrix = cv::Mat::zeros(100, 100, CV_8U);
    winManager.show(blackMatrix);
    winManager.destroyWindow();
}

TEST(Manager, CaptureManager) {
    cv::VideoCapture cam(0);
    Managers::WindowManager winManager("test");
    winManager.createWindow();
    Managers::CaptureManager capManager(cam, winManager);
    ASSERT_FALSE(capManager.get_mirrored());
    capManager.set_mirrored(true);
    ASSERT_TRUE(capManager.get_mirrored());
    capManager.enterFrame();
    ASSERT_FALSE(capManager.frame().empty());
    ASSERT_FALSE(capManager.isWritingImage());
    ASSERT_FALSE(capManager.isWritingVideo());
    capManager.startWritingVideo("test.avi");
    ASSERT_TRUE(capManager.isWritingVideo());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
