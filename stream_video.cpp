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