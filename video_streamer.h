#ifndef __VIDEO_STREAMER_H__
#define __VIDEO_STREAMER_H__

#include <memory>
#include <thread>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class VideoStreamer {
    public:
        VideoStreamer(std::string webcam_device, std::string ip_address, uint16_t port);
        ~VideoStreamer();
        void StreamVideo(void);

    private:
        cv::VideoCapture m_video_capture;
        cv::VideoWriter m_video_output;
        cv::Mat m_frame;
        cv::Mat m_output;

        int m_frame_number;
};

#endif /* __VIDEO_STREAMER_H__ */