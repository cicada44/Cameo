#include <managers/managers.hpp>

#include <opencv2/opencv.hpp>

#include <string>

namespace Managers {

#define HD_SIZE_WIDTH 1024
#define HD_SIZE_HEIGTH 768

#define LABEL_TRANSFORM_FOURIE "Transformed"
#define BAR_CONTRAST_NAME "Contrast"
#define BAR_BRIGHTNESS_NAME "Brightness"

#define CONTRAST_N_BRIGHTNESS_HIGHER_VAL 100

/**
 * @brief Does Fourier transform of inputImage.
 *
 * @param inputImage image to transform.
 * @return cv::Mat transformed image.
 */
cv::Mat fourierTransform(const cv::Mat& inputImage) {
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    grayImage.convertTo(grayImage, CV_32F);

    int m = cv::getOptimalDFTSize(grayImage.rows);
    int n = cv::getOptimalDFTSize(grayImage.cols);
    cv::Mat padded;
    cv::copyMakeBorder(grayImage, padded, 0, m - grayImage.rows, 0, n - grayImage.cols, cv::BORDER_CONSTANT,
                       cv::Scalar::all(0));

    cv::Mat complexImage;
    cv::dft(padded, complexImage, cv::DFT_COMPLEX_OUTPUT);

    cv::Mat planes[2];
    cv::split(complexImage, planes);

    cv::Mat magnitude;
    cv::magnitude(planes[0], planes[1], magnitude);

    cv::normalize(magnitude, magnitude, 0, 255, cv::NORM_MINMAX);
    cv::Mat magnitudeImage = magnitude;

    return magnitudeImage;
}

/**
 * @brief Sharpes image with [[-1, 0, -1], [-1, 5, -1], [-1, 0, -1]].
 *
 * @param inputImg image to sharp.
 * @param outputImg sharped image.
 */
void sharp(const cv::Mat& inputImg, cv::Mat& outputImg) {
    const int nChannels = inputImg.channels();
    outputImg.create(inputImg.size(), inputImg.type());
    for (int j = 1; j < inputImg.rows - 1; ++j) {
        const uchar* previous = inputImg.ptr<uchar>(j - 1);
        const uchar* current = inputImg.ptr<uchar>(j);
        const uchar* next = inputImg.ptr<uchar>(j + 1);
        uchar* output = outputImg.ptr<uchar>(j);
        for (int i = nChannels; i < nChannels * (inputImg.cols - 1); ++i) {
            output[i] = cv::saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] -
                                                 previous[i] - next[i]);
        }
    }
    outputImg.row(0).setTo(cv::Scalar(0));
    outputImg.row(outputImg.rows - 1).setTo(cv::Scalar(0));
    outputImg.col(0).setTo(cv::Scalar(0));
    outputImg.col(outputImg.cols - 1).setTo(cv::Scalar(0));
}

WindowManager::WindowManager(const std::string& windowName, const int contrast, const int brightnessVal)
    : windowName_(windowName), isWindowCreated_(false), contrastVal_(contrast), brightnessVal_(brightnessVal) {}

std::string WindowManager::getWindowName() const { return windowName_; }

bool WindowManager::isWindowCreated() const { return isWindowCreated_; }

void WindowManager::createWindow() {
    cv::namedWindow(windowName_, cv::WINDOW_NORMAL);
    isWindowCreated_ = true;
}

void WindowManager::createParticularWindow(const std::string& name) { cv::namedWindow(name, cv::WINDOW_NORMAL); }

void WindowManager::createTrackbar(const std::string& name, const int upperVal) {
    if (isWindowCreated_) cv::createTrackbar(name, windowName_, &contrastVal_, upperVal, onTrackbarStatic, this);
}

void WindowManager::createAllTrackbars() {
    createTrackbar("Brightness", CONTRAST_N_BRIGHTNESS_HIGHER_VAL);
    createTrackbar("Contrast", CONTRAST_N_BRIGHTNESS_HIGHER_VAL);
}

void WindowManager::onTrackbar(int value) { contrastVal_ = value; }

void WindowManager::onTrackbarStatic(int value, void* userdata) {
    WindowManager* obj = static_cast<WindowManager*>(userdata);
    obj->onTrackbar(value);
}

int WindowManager::get_contrast() const { return contrastVal_; }

void WindowManager::set_contrast(int newcontrast) { contrastVal_ = newcontrast; }

int WindowManager::get_brightness() const { return brightnessVal_; }

void WindowManager::set_brightness(const int newbrightness) { brightnessVal_ = newbrightness; }

void WindowManager::destroyParticularWindow(const std::string& name) { cv::destroyWindow(name); }

void WindowManager::showInParticularWindow(cv::Mat& image, const std::string& winname) { cv::imshow(winname, image); }

void WindowManager::show(const cv::Mat& frame) const { cv::imshow(windowName_, frame); }

void WindowManager::destroyWindow() {
    cv::destroyWindow(windowName_);
    isWindowCreated_ = false;
}

int WindowManager::getProcessEvent() const { return cv::waitKey(1); }

CaptureManager::CaptureManager(cv::VideoCapture& cam, WindowManager& winManager, const bool shouldMirrored,
                               const bool shouldGblure, const bool shouldMblure, const bool shouldFT,
                               const bool shouldSh)
    : winManager_(winManager),
      vidCapturer_(cam),
      shouldMirrored_(shouldMirrored),
      shouldGblured_(shouldGblure),
      shouldMBlured_(shouldMblure),
      shouldMakeFourieT_(shouldFT),
      shouldSharped_(shouldSh) {}

bool CaptureManager::get_mirrored() const { return shouldMirrored_; }

void CaptureManager::set_mirrored(const bool shMirrored) { shouldMirrored_ = shMirrored; }

bool CaptureManager::get_Gbluring() const { return shouldGblured_; }

void CaptureManager::set_Gbluring(const bool sGb) { shouldGblured_ = sGb; }

bool CaptureManager::get_Mbluring() const { return shouldGblured_; }

void CaptureManager::set_Mbluring(const bool sMb) { shouldGblured_ = sMb; }

void CaptureManager::set_FT(const bool sFt) { shouldMakeFourieT_ = sFt; }

bool CaptureManager::get_FT() const { return shouldMakeFourieT_; }

void CaptureManager::set_sh(const bool shShapr) { shouldSharped_ = shShapr; }

bool CaptureManager::get_sh() const { return shouldSharped_; }

int CaptureManager::get_channel() const { return channel_; }

void CaptureManager::set_ImageFilename(const std::string& imgFilename) { imgFilename_ = imgFilename; }

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

void CaptureManager::exitFrame(const int contrast, const int brightness) {
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
        preProcessImage(contrast, brightness);
        winManager_.show(frame_);
    }

    if (isWritingImage()) cv::imwrite(imgFilename_, frame_);

    writeVideoFrame();

    frame_.release();
    isFrameEntered_ = false;
}

void CaptureManager::showFourieTransformed() {
    cv::Mat transformedFrame = fourierTransform(frame_);
    winManager_.createParticularWindow(LABEL_TRANSFORM_FOURIE);
    winManager_.showInParticularWindow(transformedFrame, LABEL_TRANSFORM_FOURIE);
    shouldMakeFourieT_ = false;
}

void CaptureManager::preProcessImage(const int contrast, const int brightness) {
    if (shouldMirrored_) cv::flip(frame_, frame_, 1);
    if (shouldGblured_) cv::GaussianBlur(frame_, frame_, cv::Size(13, 13), 0);
    if (shouldMBlured_) cv::medianBlur(frame_, frame_, 13);
    if (shouldMakeFourieT_) showFourieTransformed();
    if (shouldSharped_) sharp(frame_, frame_);
    frame_.convertTo(frame_, CV_32F);
    cv::convertScaleAbs(frame_, frame_, 1.0 + contrast / 10, brightness);
    frame_.convertTo(frame_, CV_8U);
}

void CaptureManager::startWritingVideo(const std::string& filename, int encoding) {
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

            vidWriter_ = cv::VideoWriter(vidFilename_, vidEncoding_, fps, winSize);
        }
        vidWriter_.write(frame_);
    }
}

}  // namespace Managers
