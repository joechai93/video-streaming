# Setup and Build
Two applications are included in this repo. One is a video streamer using a webcam (/dev/video0) and another is a video receiver.  
The video apps are parameterised to take in command line arguments specifying ip address and port.  
The apps are to be run in Ubuntu 18.  


## Install opencv with gstreamer
An install script is provided (taken from opencv and modified to include gstreamer plugin) in the opencv_install directory.  

Run the script (after reading it first):  
> cd opencv_install  
> sudo ./install_opencv.sh  

This may take some time.  

## Build the streamer and receiver apps
Return to the root directory.  

> cd ../  
> mkdir build  
> cd build  
> cmake ..  
> make -j8  

## Test the apps
In a terminal, start the streaming app, specifing the loopback and port number of 1234  

> ./stream_video 127.0.0.1 1234  

In another terminal, start the receive app, specifying the port.  

> ./receive_video 1234  

It may take 5-10 seconds for the video to appear.

 
# gstreamer pipe line explanation
The gstreamer plugin with OpenCV was used to stream and receive the video.  

"x264enc tune=zerolatency ! h264parse " causes the pipeline to convert raw video into h264 compressed video format.  
"rtph264pay" encodes the payload h264 into rtp packets.  
"udpsink ..." specifies the host ip address and port number.  


# Improvements
Given more time, the following improvements could be made:  

Improve the handling of command line arguments and the usage function. Perhaps use boost program options.    
Add feature to save video or images.  
If the streaming/receiving features are to be added to an existing program, multi-threading might be used for multi tasking. Doing multi-threading correctly is difficult and time-consuming to get right.   
Investigate other encoding options.  



# GST cheat sheet pipelines


# h264 send and receive

gst-launch-1.0 v4l2src !     'video/x-raw, width=640, height=480, framerate=30/1' !     videoconvert !     x264enc pass=qual quantizer=20 tune=zerolatency !     rtph264pay !     udpsink host=localhost port=1234  
  

gst-launch-1.0 udpsrc port=1234  !     "application/x-rtp, payload=127" !     rtph264depay !     avdec_h264 !     videoconvert  !     xvimagesink sync=false  


