#include "video_streamer.h"

#include <csignal>
#include <iostream> 

bool shutdown_flag = false;

void usage();

void signalHandler( int signum ) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    shutdown_flag = true;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        usage();
        exit(0);
    }

    std::string ip_address = argv[1];
    int port_number = std::stoi(argv[2]);

    signal(SIGINT, signalHandler);  

    VideoStreamer stream_test("/dev/video0", ip_address, port_number);
    
    while (!shutdown_flag) {

        stream_test.StreamVideo();
    }

    std::cout << "Program terminating. \n";

    return 0;
}

void usage()
{
    std::cout << "./stream_video" << "[ip address] [port number]" << std::endl <<
      "Example: ./stream_video 127.0.0.1 1234" << std::endl;
}