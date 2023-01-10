#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);

    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_6X6_250);
    Ptr<aruco::DetectorParameters> params = aruco::DetectorParameters::create();

    while (true) {
        Mat frame;
        cap >> frame;

        vector<vector<Point2f> > corners;
        vector<int> ids;
        aruco::detectMarkers(frame, dictionary, corners, ids, params);

        Point2f marker1, marker2;
        if(ids.size() == 2){
            marker1 = corners[0][0];
            marker2 = corners[1][0];
            cout << "marker1 coords: " << marker1;
            cout << " | marker2 coords: " << marker2 << endl;
        }
        if(ids.size() == 1){
            marker1 = corners[0][0];
            cout << "marker coords:" << marker1 << endl;
        }
        if(ids.size() == 0){
            cout << "no markers "<< endl;
        }
       
        double distance = sqrt(pow(marker1.x - marker2.x, 2) + pow(marker1.y - marker2.y, 2));
        cout << "distance: " << distance<< endl;
    
        if (ids.size() > 0) {
            aruco::drawDetectedMarkers(frame, corners);
        }
        imshow("Webcam", frame);
    }

    return 0;
}
