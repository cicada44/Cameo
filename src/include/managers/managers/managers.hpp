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
    WindowManager(const std::string& windowName);

    /**
     * @brief Returns a copy of std::string windowName.
     *
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
     * @brief Shows frame in created window.
     */
    void show(const cv::Mat& frame) const;

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

    // void onMouse(int state, void* userdata);
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
    CaptureManager(cv::VideoCapture& cam, WindowManager& winManager,
                   const bool shouldMirrored = false,
                   const bool shouldGblure = false,
                   const bool shouldMBlure = false);

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
    void exitFrame();

    /**
     * @brief Starts writing video with filename `filename` and codec
     * `encoding`.
     * @param filename name for output file.
     * @param encoding file codec for video, default - I420.
     */
    void startWritingVideo(const std::string& filename,
                           int encoding = cv::VideoWriter::fourcc('I', '4', '2',
                                                                  '0'));

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
    bool shouldMirrored_, isFrameEntered_, shouldGblured_, shouldMBlured_;

    void writeVideoFrame();
};

class ButtonManager {
public:
private:
};

}  // namespace Managers
