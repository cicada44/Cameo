#pragma once

#include <opencv2/opencv.hpp>

#include <managers/managers.hpp>

namespace Cameo {

class CameoWrapper {
public:
    CameoWrapper() = delete;

    /**
     * @brief Creates `Cameo` with CaptureManager cM and WindowManager wM.
     * @param cM CaptureManager object.
     * @param wM WindowManager object.
     */
    CameoWrapper(Managers::CaptureManager& cM, Managers::WindowManager& wM);

    /**
     * @brief Runs the Cameo main app.
     */
    void run();

private:
    Managers::CaptureManager capManager_;
    Managers::WindowManager winManager_;

    /**
     * @brief Process events happened on keyboard.
     * @param keycode ASCII code of happened event.
     */
    void onKeypress(const int keycode);
};

}  // namespace Cameo
