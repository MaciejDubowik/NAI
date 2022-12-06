//
//  main.cpp
//  lab07
//
//  Created by Maciej Dubowik on 06/12/2022.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
// g++ `pkg-config --cflags opencv4` cv2.cpp `pkg-config --libs opencv4`
using namespace std;
using namespace cv;
int main()
{
    VideoCapture cap(0);
    
    while(true){
        Mat webcam;
        cap.read(webcam);
        flip(webcam, webcam, 1);
        imshow("webcam", webcam);
        waitKey(1);
    }
    
}




