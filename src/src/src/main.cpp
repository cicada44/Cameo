#include <Cameo/Cameo.hpp>
#include <managers/managers.hpp>

#include <iostream>

int main() {
    cv::VideoCapture mainCam(0);
    Managers::WindowManager winManager("Cameo");
    winManager.createWindow();
    Managers::CaptureManager capManager(mainCam, winManager);
    Cameo::CameoWrapper cameo(capManager, winManager);

    std::cout << "[I] Run Cameo...\n";
    cameo.run();
}
