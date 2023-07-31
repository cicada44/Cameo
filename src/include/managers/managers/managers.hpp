#pragma once

#include <opencv2/opencv.hpp>

#include <string>

namespace Managers {

class WindowManager {
public:
    /**
     * @brief Constructs a WindowManager that manages the window.
     */
    WindowManager(const std::string& windowName);

    /**
     * @brief Destroyes the windows.
     */
    ~WindowManager();

    /**
     * @brief Returns a copy of std::string windowName.
     *
     * @return std::string - name of window.
     */
    std::string getWindowName() const;

    /**
     * @brief Returns a window state.
     *
     * @return true if window is created, otherwise - fase.
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
                   const bool shouldMirrored = false);

    /* @return shouldMirrored attribute current state. */
    bool get_mirrored() const;

    /**
     * @brief Set frame mirrored state.
     * @param shMirrored new value for attribute shouldMirrored.
     */
    void set_mirrored(const bool shMirrored);

    /* @return number of channels. */
    int get_channel() const;

    /**
     * @brief Set `channels` attribute to a new value.
     * @param channels new value for `channels attribute`.
     */
    void set_channel(const int channels);

    /**
     * @brief Set image filename to the new value.
     *
     * @param filename New image filename.
     */
    void set_ImageFilename(const std::string& filename);

    /**
     * @brief Returns frame retrieved from camera. If there's no frame - does
     * nothing.
     * @return cv::Mat frame from camera.
     */
    cv::Mat frame();

    /* @return isWritingImage attribute. */
    bool isWritingImage() const;

    /* @return isWritingVideo attribute. */
    bool isWritingVideo() const;

    /**
     * @brief Process class state when enter to frame.
     */
    void enterFrame();

    /**
     * @brief Process class state when exit from frame.
     */
    void exitFrame();

    /** Starts writing video with filename `filename` and codec `encoding`.
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
    bool shouldMirrored_, isFrameEntered_;

    void writeVideoFrame();
};

}  // namespace Managers
