cmake_minimum_required(VERSION 3.0.2)
project(read_dk_rgb)

## Compile as C++11, supported in ROS Kinetic and newer

# Enable C++11
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  image_transport
  cv_bridge
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES read_dk_rgb
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)

# Kinect DK相机
find_package(k4a REQUIRED)# 关键。因为后面的target_link_libraries中用到了k4a::k4a，所以在这儿加了一行，否则会显示未定义声明
# Find OpenCV
find_package(OpenCV REQUIRED)

# Add includes
include_directories( ${catkin_INCLUDE_DIRS} )
include_directories( ${CMAKE_CURRENT_LIST_DIR} ) # 包含当前目录下我的头文件
include_directories( ${OpenCV_INCLUDE_DIRS} )
 
# Declare the executable target built from your sources
add_executable( read_dk_rgb src/main.cpp )
add_executable( pic_conv src/pic_conv.cpp )
add_executable( sub_image src/sub_image.cpp )

# Link your application with other libraries
target_link_libraries(read_dk_rgb k4a::k4a ${OpenCV_LIBS})
target_link_libraries(pic_conv ${OpenCV_LIBS})
target_link_libraries(sub_image ${OpenCV_LIBS} ${catkin_LIBRARIES})


 
 