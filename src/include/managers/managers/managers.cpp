#include <managers/managers.hpp>

#include <opencv2/opencv.hpp>

#include <string>

namespace Managers {

#define HD_SIZE_WIDTH 1024
#define HD_SIZE_HEIGTH 768

WindowManager::WindowManager(const std::string& windowName)
    : windowName_(windowName), isWindowCreated_(false) {}

std::string WindowManager::getWindowName() const { return windowName_; }

bool WindowManager::isWindowCreated() const { return isWindowCreated_; }

void WindowManager::createWindow() {
    cv::namedWindow(windowName_, cv::WINDOW_NORMAL);
    isWindowCreated_ = true;
}

void WindowManager::show(const cv::Mat& frame) const {
    cv::imshow(windowName_, frame);
}

void WindowManager::destroyWindow() {
    cv::destroyWindow(windowName_);
    isWindowCreated_ = false;
}

int WindowManager::getProcessEvent() const { return cv::waitKey(1); }

CaptureManager::CaptureManager(cv::VideoCapture& cam, WindowManager& winManager,
                               const bool shouldMirrored,
                               const bool shouldGblure, const bool shouldMblure)
    : winManager_(winManager),
      vidCapturer_(cam),
      shouldMirrored_(shouldMirrored),
      shouldGblured_(shouldGblure),
      shouldMBlured_(shouldMblure) {}

bool CaptureManager::get_mirrored() const { return shouldMirrored_; }

void CaptureManager::set_mirrored(const bool shMirrored) {
    shouldMirrored_ = shMirrored;
}

bool CaptureManager::get_Gbluring() const { return shouldGblured_; }

void CaptureManager::set_Gbluring(const bool sGb) { shouldGblured_ = sGb; }

bool CaptureManager::get_Mbluring() const { return shouldGblured_; }

void CaptureManager::set_Mbluring(const bool sMb) { shouldGblured_ = sMb; }

int CaptureManager::get_channel() const { return channel_; }

void CaptureManager::set_ImageFilename(const std::string& imgFilename) {
    imgFilename_ = imgFilename;
}

cv::Mat CaptureManager::frame() {
    if (isFrameEntered_ == true) {
        vidCapturer_.retrieve(frame_);
    }

    return frame_;
}

bool CaptureManager::isWritingImage() const { return !imgFilename_.empty(); }

bool CaptureManager::isWritingVideo() const { return !vidFilename_.empty(); }

void CaptureManager::enterFrame() {
    if (vidCapturer_.isOpened()) isFrameEntered_ = vidCapturer_.grab();
}

void CaptureManager::exitFrame() {
    if (frame_.empty()) {
        isFrameEntered_ = false;
        return;
    }

    if (framesElapsed_ == 0) {
        startTime_ = std::time(nullptr);
    } else {
        std::time_t timeElapsed = std::difftime(std::time(nullptr), startTime_);
        if (timeElapsed != 0) fpsEstimate_ = framesElapsed_ / timeElapsed;
    }

    ++framesElapsed_;

    if (winManager_.isWindowCreated()) {
        if (shouldMirrored_)
            cv::flip(frame_, frame_, 1);
        if (shouldGblured_) 
            cv::GaussianBlur(frame_, frame_, cv::Size(13, 13), 0);
        if (shouldMBlured_) 
            cv::medianBlur(frame_, frame_, 13);

        winManager_.show(frame_);
    }

    if (isWritingImage()) cv::imwrite(imgFilename_, frame_);

    writeVideoFrame();

    frame_.release();
    isFrameEntered_ = false;
}

void CaptureManager::startWritingVideo(const std::string& filename,
                                       int encoding) {
    vidFilename_ = filename;
    vidEncoding_ = encoding;
}

void CaptureManager::stopWritingVideo() {
    vidEncoding_ = -1;
    vidFilename_.clear();
    vidWriter_.release();
}

void CaptureManager::writeVideoFrame() {
    if (isWritingVideo()) {
        if (!vidWriter_.isOpened()) {
            static double fps = vidWriter_.get(cv::CAP_PROP_FPS);
            if (fps == 0.0) {
                if (framesElapsed_ < 20)
                    return;
                else
                    fps = fpsEstimate_;
            }

            cv::Size winSize(int(vidCapturer_.get(cv::CAP_PROP_FRAME_WIDTH)),
                             int(vidCapturer_.get(cv::CAP_PROP_FRAME_HEIGHT)));

            std::cerr << int(vidCapturer_.get(cv::CAP_PROP_FRAME_WIDTH)) << ' '
                      << int(vidCapturer_.get(cv::CAP_PROP_FRAME_HEIGHT))
                      << '\n';

            vidWriter_ =
                cv::VideoWriter(vidFilename_, vidEncoding_, fps, winSize);
        }
        vidWriter_.write(frame_);
    }
}

}  // namespace Managers
