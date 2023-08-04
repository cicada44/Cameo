#include <opencv2/opencv.hpp>

#include <Cameo/Cameo.hpp>
#include <managers/managers.hpp>

namespace Cameo {

#define LABEL_DEFAULT_NAME_IMAGE "screenshot.png"
#define LABEL_DEFAULT_NAME_VIDEO "screenvideo.avi"

CameoWrapper::CameoWrapper(Managers::CaptureManager& cM, Managers::WindowManager& wM)
    : capManager_(cM), winManager_(wM) {}

void CameoWrapper::run() {
    winManager_.createWindow();
    winManager_.createTrackbar("Adjust and brightness");
    while (winManager_.isWindowCreated()) {
        capManager_.enterFrame();
        cv::Mat frame = capManager_.frame();
        capManager_.exitFrame(winManager_.get_contrast());
        onKeypress(winManager_.getProcessEvent());
    }
}

void CameoWrapper::onKeypress(const int keycode) {
    switch (keycode) {
        case 32: /* Space. */
            capManager_.set_ImageFilename(LABEL_DEFAULT_NAME_IMAGE);
            break;

        case 9: /* Tab. */
            if (!capManager_.isWritingVideo())
                capManager_.startWritingVideo(LABEL_DEFAULT_NAME_VIDEO);
            else
                capManager_.stopWritingVideo();
            break;

        case 27: /* Escape. */
            winManager_.destroyWindow();
            break;

        case 109: /* 'm' key. */
            capManager_.set_mirrored(!capManager_.get_mirrored());
            break;

        case 103: /* 'g`  key.*/
            capManager_.set_Gbluring(!capManager_.get_Gbluring());
            break;

        case 104: /* 'h' key. */
            capManager_.set_Mbluring(!capManager_.get_Mbluring());
            break;

        case 102: /* 'f' key. */
            capManager_.set_FT(true);
            break;

        case 115: /* 's' key. */
            capManager_.set_sh(!capManager_.get_sh());
            break;

        default:
            break;
    }
}

}  // namespace Cameo
