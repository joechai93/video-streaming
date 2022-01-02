cmake_minimum_required(VERSION 3.14.4)
project(receive_video CXX)
file(GLOB_RECURSE data res/* )
file(COPY ${data} DESTINATION .)
find_package(OpenCV 4.1.0 REQUIRED PATHS /usr/local/lib/cmake/opencv4 )

add_executable(stream_video stream_video.cpp video_streamer.cpp face_detector.cpp)
add_executable(receive_video receive_video.cpp)

target_link_libraries(stream_video ${OpenCV_LIBS})
target_link_libraries(receive_video ${OpenCV_LIBS})
