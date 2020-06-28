#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream> 
#include <csignal>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

bool shutdown_flag = false;
void usage();

void signalHandler( int signum ) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    shutdown_flag = true;
}


int main(int argc, char** argv)
{
    if (argc != 2)
    {
        usage();
        exit(0);
    }

    int port_number = std::stoi(argv[1]);

    cv::VideoCapture video_capture;
    std::string gstreamer_pipe = "udpsrc port=" + std::to_string(port_number) + " !  application/x-rtp, payload=127 !     rtph264depay !     avdec_h264 !     videoconvert  ! appsink";

    video_capture.open(gstreamer_pipe, cv::CAP_GSTREAMER);
    if (!video_capture.isOpened()) {
        printf("Video capture failed to open!!!!\n");
        exit (1);
    }
    cv::Mat received_frame;

    while(!shutdown_flag)
    {
        video_capture.read(received_frame);

        cv::imshow("Received Video", received_frame);
        cv::waitKey(1);
    }

    std::cout << "Program terminating. \n";

    return 0;
}

void usage()
{
    std::cout << "./receive_video" << " [port number]" << std::endl <<
      "Example: ./receive_video 1234" << std::endl;
}