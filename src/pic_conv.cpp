// C++
#include <iostream>
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Load a .jpg image from file
    Mat img = imread("/home/zh/calibrate_ws/src/livox_camera_lidar_calibration/data/photo/jpg_form.jpg", 1); // 1 means color image
    // Check if the image is loaded successfully
    if (img.empty())
    {
        std::cout << "Error: could not load image" << std::endl;
        return -1;
    }
    // Save the image as .bmp format
    bool result1 = imwrite("/home/zh/calibrate_ws/src/livox_camera_lidar_calibration/data/photo/bmp_form.bmp", img);
    bool result2 = imwrite("/home/zh/calibrate_ws/src/livox_camera_lidar_calibration/data/photo/png_form.png", img);

    // Check if the image is saved successfully
    if (result1 && result2)
    {
        std::cout << "Image saved success" << std::endl;
    }
    else
    {
        std::cout << "Error: save fail" << std::endl;
    }

    return 0;
}