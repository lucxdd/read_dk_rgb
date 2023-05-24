// 引入需要的头文件
#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat imgCallback;

// 定义一个图像回调函数，当收到新的图像时会被调用
void imageCallback(const sensor_msgs::CompressedImageConstPtr& msg) {
  try {
    cv_bridge::CvImagePtr cv_ptr_compressed =
        cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    imgCallback = cv_ptr_compressed->image;
    bool result1 = imwrite("/home/zh/Pictures/image_png.png", imgCallback);
    if (result1) ROS_INFO("save image succss");
    cv::imshow("imgCallback", imgCallback);
    // 显示函数和刷新函数一起使用，否则无法正常显示。
    cv::waitKey(1000);

    std::cout << "cv_ptr_compressed: " << cv_ptr_compressed->image.cols
              << " h: " << cv_ptr_compressed->image.rows << std::endl;
  } catch (cv_bridge::Exception& e) {
    ROS_ERROR("can not convert!\n");
  }
}

// 定义主函数
int main(int argc, char** argv) {
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;

  ros::Subscriber image_sub =
      nh.subscribe("/rgb/image_raw/compressed", 1, imageCallback);

  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    ROS_INFO("ROS OK!");
    ros::spinOnce();
  }
  return 0;
}