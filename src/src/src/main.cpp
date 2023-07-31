#include <Cameo/Cameo.hpp>
#include <managers/managers.hpp>

#include <iostream>

int main() {
    std::cout << "[I] Run Cameo...\n";

    cv::VideoCapture mainCam(0);
    Managers::WindowManager winManager("Cameo");
    winManager.createWindow();
    Managers::CaptureManager capManager(mainCam, winManager);
    Cameo::CameoWrapper cameo(capManager, winManager);

    cameo.run();
}
