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

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
