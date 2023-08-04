#pragma once

#include <opencv2/opencv.hpp>

#include <string>

namespace Managers {

class WindowManager {
public:
    bool isButtonClicked_;

    /**
     * @brief Constructs a WindowManager that manages the window.
     */
    WindowManager(const std::string& windowName, const int contrastVal = 0, const int brightnessVal = 0);

    /**
     * @brief Returns a copy of std::string windowName.
     * @return std::string - name of window.
     */
    std::string getWindowName() const;

    /**
     * @brief Returns a window state.
     *
     * @return true if window is created, otherwise - false.
     */
    bool isWindowCreated() const;

    /**
     * @brief Creates a window with name windowName.
     */
    void createWindow();

    /**
     * @brief Creates new window with particular name.
     * @param name name of new window.
     */
    void createParticularWindow(const std::string& name);

    /**
     * @brief Creates a trackbar object.
     * @param name name for bar.
     */
    void createTrackbar(const std::string& name, const int upperVal);

    /**
     * @brief Create all trackbars.
     */
    void createAllTrackbars();

    /**
     * @brief Destroyes window with particular name.
     * @param name window name that should be destroyed.
     */
    void destroyParticularWindow(const std::string& name);

    /**
     * @brief Show frame in particular window.
     * @param image image to show.
     * @param winname name of window to show image.
     */
    void showInParticularWindow(cv::Mat& image, const std::string& winname);

    /**
     * @brief Shows frame in created window.
     */
    void show(const cv::Mat& frame) const;

    /** @return Contrast value. */
    int get_contrast() const;

    /** @brief Sets new value to the contrast parameter. */
    void set_contrast(int newContrast);

    /** @return Brightness value. */
    int get_brightness() const;

    /** @brief Sets new value to the brightness parameter. */
    void set_brightness(int newBrightness);

    /**
     * @brief Destroyes window.
     */
    void destroyWindow();

    /**
     * @brief Gets keycode of next event.
     * @return ASCII code of processing event.
     */
    int getProcessEvent() const;

private:
    std::string windowName_;
    bool isWindowCreated_;
    int contrastVal_, brightnessVal_;

    /**
     * @brief Changes trackbar value.
     * @param value new value for trackbar.
     */
    void onTrackbar(int value);

    /**
     * @brief Wrapper of onTrackbar function.
     * @param value new value for trackbar.
     * @param userdata `this` argument.
     */
    static void onTrackbarStatic(int value, void* userdata);
};

class CaptureManager {
public:
    /**
     * @brief Main constructor.
     *
     * @param cam camera for controlling.
     * @param winManager WindowManager object that controls window.
     * @param shouldMirrored true - if showing frame should be mirrored,
     * otherwise - false (default).
     */
    CaptureManager(cv::VideoCapture& cam, WindowManager& winManager, const bool shouldMirrored = false,
                   const bool shouldGblure = false, const bool shouldMBlure = false, const bool shouldFT = false,
                   const bool shouldSh = false);

    /** @return shouldMirrored attribute current state. */
    bool get_mirrored() const;

    /**
     * @brief Set frame mirrored state.
     * @param shMirrored new value for attribute shouldMirrored.
     */
    void set_mirrored(const bool shMirrored);

    /** @return number of channels. */
    int get_channel() const;

    /**
     * @brief Set `channels` attribute to a new value.
     * @param channels new value for `channels` attributed.
     */
    void set_channel(const int channels);

    /**
     * @brief Set image filename to the new value.
     *
     * @param filename New image filename.
     */
    void set_ImageFilename(const std::string& filename);

    /** @return shouldGaussianBlure parameter. */
    bool get_Gbluring() const;

    /**
     * @brief Set `shouldGaussianBluring` attribute to a new value.
     * @param channels new value for `shouldGaussianBluring` attribute.
     */
    void set_Gbluring(const bool sGb);

    /** @return shouldMBlure parameter. */
    bool get_Mbluring() const;

    /**
     * @brief Set `shouldMBluring` attribute to a new value.
     * @param channels new value for `shouldMBluring` attribute.
     */
    void set_Mbluring(const bool sMb);

    /**
     * @brief Set `shouldFourieTransform` attribute to a new value.
     * @param channels new value for `shouldFourieTransform` attribute.
     */
    void set_FT(const bool sFt);

    /** @return shouldFourieTransform parameter. */
    bool get_FT() const;

    /**
     * @brief Set `shouldSharp` attribute to a new value.
     * @param channels new value for `shouldSharp` attribute.
     */
    void set_sh(const bool sFt);

    /** @return shouldSharp parameter. */
    bool get_sh() const;

    /**
     * @brief Returns frame retrieved from camera. If there's no frame - does
     * nothing.
     * @return cv::Mat frame from camera.
     */
    cv::Mat frame();

    /** @return isWritingImage attribute. */
    bool isWritingImage() const;

    /** @return isWritingVideo attribute. */
    bool isWritingVideo() const;

    /**
     * @brief Process class state when enter to frame.
     */
    void enterFrame();

    /**
     * @brief Process class state when exit from frame.
     */
    void exitFrame(const int adjust, const int brightness);

    /**
     * @brief Starts writing video with filename `filename` and codec
     * `encoding`.
     * @param filename name for output file.
     * @param encoding file codec for video, default - I420.
     */
    void startWritingVideo(const std::string& filename, int encoding = cv::VideoWriter::fourcc('I', '4', '2', '0'));

    /**
     * @brief This does what you think it does.
     */
    void stopWritingVideo();

private:
    WindowManager winManager_;
    cv::VideoWriter vidWriter_;
    cv::VideoCapture vidCapturer_;
    cv::Mat frame_;
    std::time_t startTime_;
    std::string imgFilename_, vidFilename_;
    int channel_, framesElapsed_, fpsEstimate_, vidEncoding_;
    bool shouldMirrored_, isFrameEntered_, shouldGblured_, shouldMBlured_, shouldMakeFourieT_, shouldSharped_;

    /**
     * @brief Writes video frame if needed.
     */
    void writeVideoFrame();

    /**
     * @brief Does and shows Fourie transformation result.
     */
    void showFourieTransformed();

    /**
     * @brief Processes image with should* parameters.
     */
    void preProcessImage(const int contrast, const int brightness);
};

class ButtonManager {
public:
private:
};

}  // namespace Managers
