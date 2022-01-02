/*
MIT License

Copyright (c) 2021 Joe Chai

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

#include <opencv2/core/types_c.h>
#include "opencv2/highgui.hpp"
#include "face_detector.hpp"

cv::Mat FaceDetector::DetectAndDraw( cv::Mat& img, cv::CascadeClassifier& cascade,
                    cv::CascadeClassifier& nestedCascade,
                    double scale)
{
    std::vector<cv::Rect> faces, faces2;
    cv::Mat gray, smallImg;
  
    cv::cvtColor( img, gray, cv::COLOR_BGR2GRAY ); // Convert to Gray Scale
    double fx = 1 / scale;
  
    // Resize the Grayscale Image 
    cv::resize( gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR ); 
    cv::equalizeHist( smallImg, smallImg );
  
    // Detect faces of different sizes using cascade classifier 
    cascade.detectMultiScale( smallImg, faces, 1.1, 
                            2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
  
    // Draw circles around the faces
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cv::Rect r = faces[i];
        cv::Mat smallImgROI;
        std::vector<cv::Rect> nestedObjects;
        cv::Point center;
        cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing tool
        int radius;
  
        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5)*scale);
            center.y = cvRound((r.y + r.height*0.5)*scale);
            radius = cvRound((r.width + r.height)*0.25*scale);
            cv::circle( img, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                    cvPoint(cvRound((r.x + r.width-1)*scale), 
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg( r );
          
        // Detection of eyes int the input image
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.1, 2,
                                        0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) ); 
          
        // Draw circles around eyes
        for ( size_t j = 0; j < nestedObjects.size(); j++ ) 
        {
            cv::Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
    }
  
    // Show Processed Image with detected faces
    return img;
}