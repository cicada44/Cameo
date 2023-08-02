#include <opencv2/opencv.hpp>

#include <Cameo/Cameo.hpp>
#include <managers/managers.hpp>

namespace Cameo {

CameoWrapper::CameoWrapper(Managers::CaptureManager& cM,
                           Managers::WindowManager& wM)
    : capManager_(cM), winManager_(wM) {}

void CameoWrapper::run() {
    winManager_.createWindow();
    while (winManager_.isWindowCreated()) {
        capManager_.enterFrame();
        cv::Mat frame = capManager_.frame();
        capManager_.exitFrame();
        onKeypress(winManager_.getProcessEvent());
    }
}

void CameoWrapper::onKeypress(const int keycode) {
    switch (keycode) {
        case 32: /* Space. */
            capManager_.set_ImageFilename("screenshot.png");
            break;

        case 9: /* Tab. */
            if (!capManager_.isWritingVideo())
                capManager_.startWritingVideo("screenvideo.avi");
            else
                capManager_.stopWritingVideo();
            break;

        case 27: /* Escape. */
            winManager_.destroyWindow();
            break;

        case 109: /* 'm' key. */
            (capManager_.get_mirrored() == true)
                ? capManager_.set_mirrored(false)
                : capManager_.set_mirrored(true);
            break;

        case 103: /* 'g`  key.*/
            (capManager_.get_Gbluring() == true)
                ? capManager_.set_Gbluring(false)
                : capManager_.set_Gbluring(true);
            break;

        case 104: /* 'h' key. */
            (capManager_.get_Mbluring() == true)
                ? capManager_.set_Mbluring(false)
                : capManager_.set_Mbluring(true);
            break;

        default:
            break;
    }
}

}  // namespace Cameo
