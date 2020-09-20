/*
MIT License

Copyright (c) 2020 Joe Chai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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