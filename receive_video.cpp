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