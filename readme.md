# 1、订阅图像话题并保存
```bash
# 订阅的话题为：/rgb/image_raw/compressed
# 图片保存的路径需要修改成自己的路径
# 只会保存Ctrl+C按下前的最后一张图片
rosrun read_dk_rgb sub_image
```
# 2、图像话题转换
## 2.1 安装依赖
```bash
sudo apt get install image_transport
sudo apt get install image_transport_plugins  # 该组件必须安装以便进行压缩传输。
# 在ros中，如果通过raw格式进行数据传输的话， 图像传输可能会卡顿而且录包时特别占空间，这时候就可以用compressed格式传输，然后转换成raw格式
```
## 2.2 运行
```
单独运行launch文件，源代码在image_transport库中
roslaunch read_dk_rgb image_repub.launch 
话题转换：    /rgb/image_raw/compressed    ---> /rgb/image
格式转换： sensor_msgs/CompressedImage  ---> sensor_msgs/Image
```
# 3、图片转换
```bash
# 功能：图片格式转换，例如jpg转png，png转bmp
# 需要改pic_image.cpp中的图片传入路径和输出路径
rosrun read_dk_rgb pic_conv
```