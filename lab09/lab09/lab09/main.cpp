#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(){
    float markerLength = 0.024f;

    Mat cameraMatrix = Mat::eye(3, 3, CV_32F);
    Mat distCoeffs;

    VideoCapture cap(0);

    cv::Ptr<aruco::Dictionary> dictionary = cv::makePtr<aruco::Dictionary>(aruco::getPredefinedDictionary(aruco::DICT_6X6_250));
    cv::Ptr<aruco::DetectorParameters> params = cv::makePtr<aruco::DetectorParameters>();

    while (true) {
        Mat frame;
        cap >> frame;

        vector<vector<Point2f> > corners;
        vector<int> ids;
        aruco::detectMarkers(frame, dictionary, corners, ids, params);

        Point2f marker1, marker2;
        if(ids.size() == 1){
            marker1 = corners[0][0];
            cout << "marker coords:" << marker1 << endl;
        }
        if(ids.size() == 0){
            cout << "no markers "<< endl;
        }
       
        if(ids.size() >= 2){
            vector<Vec3d> rvecs, tvecs;
            aruco::estimatePoseSingleMarkers(corners, markerLength, cameraMatrix, distCoeffs, rvecs, tvecs);
        
            Vec3d translation1 = tvecs[0];
            Vec3d translation2 = tvecs[1];

            double distance = sqrt(pow(translation1[0] - translation2[0], 2) +
                                   pow(translation1[1] - translation2[1], 2) +
                                   pow(translation1[2] - translation2[2], 2));
            
            distance = distance * 100;
            cout << "distance: " << distance << "cm" << endl;
        }

        if (ids.size() > 0) {
            aruco::drawDetectedMarkers(frame, corners);
        }
        imshow("Webcam", frame);
        
        if (waitKey(1) == 27) {
              break;
          }
    }

    return 0;
}

