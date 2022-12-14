#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
    Scalar lower = Scalar(15, 150, 20);
    Scalar upper = Scalar(35, 255, 255);

    VideoCapture webcam_video(0);
    std::vector<Point> centers;
    while (true)
    {
        
        Mat video;
        webcam_video.read(video);

        Mat img;
        cvtColor(video, img, COLOR_BGR2HSV);

        Mat mask;
        inRange(img, lower, upper, mask);

        std::vector<std::vector<Point> > mask_contours;
        findContours(mask, mask_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        
        std::sort(mask_contours.begin(), mask_contours.end(),
                  [](const std::vector<Point>& contour1, const std::vector<Point>& contour2) {
                      return contourArea(contour1) > contourArea(contour2);
                  });

        if (mask_contours.size() > 2)
        {
            mask_contours.resize(2);
        }

        std::vector<Point> centers;
        for (int i = 0; i < mask_contours.size(); i++)
        {
            Moments moments = cv::moments(mask_contours[i]);
            int x = moments.m10 / moments.m00;
            int y = moments.m01 / moments.m00;
            centers.push_back(Point(x, y));
            
            if (centers.size() == 2 && abs(centers[0].y - centers[1].y) <= 50)
            {
                
                line(video, centers[0], centers[1], Scalar(0, 0, 255), 15);
                line(video, centers[0], centers[1], Scalar(255, 0, 0), 10);
                line(video, centers[0], centers[1], Scalar(0, 255, 0), 3);
            }
        
        }
        
        if (!mask_contours.empty())
        {
            for (const auto& mask_contour : mask_contours)
            {
                if (contourArea(mask_contour) > 500)
                {
                    Rect rect = boundingRect(mask_contour);
                    rectangle(video, rect, Scalar(0, 0, 255), 3);
                }
            }
        }
        
        imshow("mask image", mask);
        imshow("window", video);
        waitKey(1);
    }

    return 0;
}
