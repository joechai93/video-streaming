#include "video_streamer.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>


VideoStreamer::VideoStreamer(std::string webcam_device, std::string ip_address, uint16_t port)
    : m_video_capture{}
    , m_video_output{}
    , m_frame{}
    , m_output{}
    , m_frame_number{0}
{

    std::string gstreamer_pipeline_in = "v4l2src device=" + webcam_device + " ! video/x-raw,framerate=30/1,width=640,height=480 ! videoconvert ! appsink";

    m_video_capture.open(gstreamer_pipeline_in.c_str(), cv::CAP_GSTREAMER);

    // m_video_capture.open("videotestsrc pattern=ball ! videoconvert ! appsink", cv::CAP_GSTREAMER);

    if (!m_video_capture.isOpened()) {
        printf("Video capture failed to open!!!!\n");
        exit (1);
    }
    m_video_capture.read(m_frame);
    
    std::string gstreamer_pipeline_out = "appsrc ! queue !  videoconvert ! video/x-raw ! x264enc tune=zerolatency ! h264parse ! rtph264pay ! udpsink host=" 
    + ip_address + " port=" + std::to_string(port) + " sync=true";

    m_video_output.open(gstreamer_pipeline_out.c_str(),
        cv::CAP_GSTREAMER,
        0,
        30,
        m_frame.size(),
        true);

    if (!m_video_output.isOpened()) {
        printf("Video output failed to open!!!!\n");
        exit (1);
    }
}

VideoStreamer::~VideoStreamer()
{
}


void VideoStreamer::StreamVideo(void)
{
    m_video_capture.read(m_frame);
    // cv::imshow("hi",m_frame);
    // cv::waitKey(1);

    std::string text_overlay = "Frame number: " + std::to_string(m_frame_number); 
    cv::putText(m_frame, text_overlay, cv::Point(50,50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,0,0), 3);

    // filter and canny edge detect just for fun
    //cv::medianBlur(mask, mask, 5);
    // cv::GaussianBlur(m_frame, m_frame, cv::Size(7,7), 2);
    // cv::Mat contours;
    // cv::Canny(m_frame, contours, 290, 350);

    m_video_output.write(m_frame);


    m_frame_number += 1;
}


