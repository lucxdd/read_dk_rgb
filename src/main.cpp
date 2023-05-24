// C++
#include <iostream>
// OpenCV
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;
// Kinect DK
#include <k4a/k4a.hpp>

using namespace cv;
// 宏
// 方便控制是否 std::cout 信息
#define DEBUG_std_cout 0

int main(int argc, char *argv[]) {
  // 发现已连接的设备数
  const uint32_t device_count = k4a::device::get_installed_count();
  if (0 == device_count) {
    std::cout << "Error: no K4A devices found. " << std::endl;
    return EXIT_FAILURE;
  } else {
    std::cout << "Found " << device_count << " connected devices. "
              << std::endl;

    if (1 != device_count)  // 超过1个设备，也输出错误信息。
    {
      std::cout << "Error: more than one K4A devices found. " << std::endl;
      return EXIT_FAILURE;
    } else  // 该示例代码仅限对1个设备操作
    {
      std::cout << "Done: found 1 K4A device. " << std::endl;
    }
  }
  // 打开（默认）设备
  k4a::device device = k4a::device::open(K4A_DEVICE_DEFAULT);
  std::cout << "Done: open device. " << std::endl;

  /*
          检索 Azure Kinect 图像数据
  */
  // 配置并启动设备
  k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
  config.camera_fps = K4A_FRAMES_PER_SECOND_15;
  config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
  config.color_resolution = K4A_COLOR_RESOLUTION_1080P;
  // config.depth_mode = K4A_DEPTH_MODE_NFOV_UNBINNED;
  //   config.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
  // ensures that depth and color images are both available in the capture
  //   config.synchronized_images_only = true;

  device.start_cameras(&config);
  std::cout << "Done: start camera." << std::endl;

  // 稳定化
  k4a::capture capture;
  int iAuto = 0;       // 用来稳定，类似自动曝光
  int iAutoError = 0;  // 统计自动曝光的失败次数
  while (true) {
    if (device.get_capture(&capture)) {
      std::cout << iAuto << ". Capture several frames to give auto-exposure"
                << std::endl;

      // 跳过前 n 个（成功的数据采集）循环，用来稳定
      if (iAuto != 30) {
        iAuto++;
        continue;
      } else {
        std::cout << "Done: auto-exposure" << std::endl;
        break;  // 跳出该循环，完成相机的稳定过程
      }
    } else {
      std::cout << iAutoError << ". K4A_WAIT_RESULT_TIMEOUT." << std::endl;
      if (iAutoError != 30) {
        iAutoError++;
        continue;
      } else {
        std::cout << "Error: failed to give auto-exposure. " << std::endl;
        return EXIT_FAILURE;
      }
    }
  }
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "----- Have Started Kinect DK. -----" << std::endl;
  std::cout << "-----------------------------------" << std::endl;

  // 从设备获取捕获
  k4a::image rgbImage;
  //   k4a::image depthImage;
  //   k4a::image irImage;

  cv::Mat cv_rgbImage_with_alpha;
  cv::Mat cv_rgbImage_no_alpha;
  //   cv::Mat cv_depth;
  //   cv::Mat cv_depth_8U;
  //   cv::Mat cv_irImage;
  //   cv::Mat cv_irImage_8U;

  // while (true)

  for (size_t i = 0; i < 1; i++)
  {
    // if (device.get_capture(&capture, std::chrono::milliseconds(0)))
    if (device.get_capture(&capture)) {
      // rgb
      /* Each pixel of BGRA32 data is four bytes.
         The first three bytes represent Blue, Green, and Red data.
         The fourth byte is the alpha channel and is unused in the Azure Kinect
         APIs.
      */
      rgbImage = capture.get_color_image();
#if DEBUG_std_cout == 1
      std::cout << "[rgb] "
                << "\n"
                << "format: " << rgbImage.get_format() << "\n"
                << "device_timestamp: "
                << rgbImage.get_device_timestamp().count() << "\n"
                << "system_timestamp: "
                << rgbImage.get_system_timestamp().count() << "\n"
                << "height*width: " << rgbImage.get_height_pixels() << ", "
                << rgbImage.get_width_pixels() << std::endl;
#endif
      cv_rgbImage_with_alpha =
          cv::Mat(rgbImage.get_height_pixels(), rgbImage.get_width_pixels(),
                  CV_8UC4, (void *)rgbImage.get_buffer());
      cv::cvtColor(cv_rgbImage_with_alpha, cv_rgbImage_no_alpha,
                   cv::COLOR_BGRA2BGR);
      cv::imwrite("/home/zh/dataset/photo/new.jpg", cv_rgbImage_no_alpha, {cv::IMWRITE_JPEG_QUALITY, 100});
      cv::imwrite("/home/zh/dataset/photo/new.png", cv_rgbImage_no_alpha);

      // depth
      // * Each pixel of DEPTH16 data is two bytes of little endian unsigned
      // depth data. The unit of the data is in
      // * millimeters from the origin of the camera.

      //       depthImage = capture.get_depth_image();
      // #if DEBUG_std_cout == 1
      //       std::cout << "[depth] "
      //                 << "\n"
      //                 << "format: " << depthImage.get_format() << "\n"
      //                 << "device_timestamp: "
      //                 << depthImage.get_device_timestamp().count() << "\n"
      //                 << "system_timestamp: "
      //                 << depthImage.get_system_timestamp().count() << "\n"
      //                 << "height*width: " << depthImage.get_height_pixels()
      //                 << ", "
      //                 << depthImage.get_width_pixels() << std::endl;
      // #endif
      //       cv_depth =
      //           cv::Mat(depthImage.get_height_pixels(),
      //           depthImage.get_width_pixels(),
      //                   CV_16U, (void *)depthImage.get_buffer(),
      //                   static_cast<size_t>(depthImage.get_stride_bytes()));
      //       cv_depth.convertTo(cv_depth_8U, CV_8U, 1);

      //       // ir
      //       // * Each pixel of IR16 data is two bytes of little endian
      //       unsigned depth
      //       // data. The value of the data represents
      //       // * brightness.
      //       irImage = capture.get_ir_image();
      // #if DEBUG_std_cout == 1
      //       std::cout << "[ir] "
      //                 << "\n"
      //                 << "format: " << irImage.get_format() << "\n"
      //                 << "device_timestamp: "
      //                 << irImage.get_device_timestamp().count() << "\n"
      //                 << "system_timestamp: "
      //                 << irImage.get_system_timestamp().count() << "\n"
      //                 << "height*width: " << irImage.get_height_pixels() <<
      //                 ", "
      //                 << irImage.get_width_pixels() << std::endl;
      // #endif
      //       cv_irImage =
      //           cv::Mat(irImage.get_height_pixels(),
      //           irImage.get_width_pixels(),
      //                   CV_16U, (void *)irImage.get_buffer(),
      //                   static_cast<size_t>(irImage.get_stride_bytes()));
      //       cv_irImage.convertTo(cv_irImage_8U, CV_8U, 1);

      // show image
      cv::imshow("color", cv_rgbImage_no_alpha);
      // cv::imshow("depth", cv_depth_8U);
      // cv::imshow("ir", cv_irImage_8U);
      cv::waitKey(1);

      std::cout << "--- test ---" << std::endl;
    } else {
      std::cout << "false: K4A_WAIT_RESULT_TIMEOUT." << std::endl;
    }
  }

  cv::destroyAllWindows();

  // 释放，关闭设备
  rgbImage.reset();
  // depthImage.reset();
  // irImage.reset();
  capture.reset();
  device.close();

  return EXIT_SUCCESS;
}