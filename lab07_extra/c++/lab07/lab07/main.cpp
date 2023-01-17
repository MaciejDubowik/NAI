#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0);
    while(true)
    {
        double start_time = clock();
        Mat webcam;
        cap.read(webcam);
        flip(webcam, webcam, 1);
        cvtColor(webcam,webcam,COLOR_BGR2GRAY);
        Canny(webcam,webcam,50,150);
        vector<vector<Point> > contours;
        findContours(webcam, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        int largest_area = 0;
        int largest_contour_index = 0;
        for (int i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);
            if (area > largest_area) {
                largest_area = area;
                largest_contour_index = i;
            }
        }
        drawContours(webcam, contours, largest_contour_index, Scalar(0, 255, 0), 3);
        imshow("webcam", webcam);
        double time_taken = (clock() - start_time) / CLOCKS_PER_SEC;

        if (waitKey(1) == 27) {
            cout<<"Time taken: "<<time_taken<<endl;
            break;
        }
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
