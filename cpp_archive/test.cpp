/****
     Combine sensor_msgs/Image and sensor_msgs/PointCloud2
****/
/***
    Author: Li Jue Kun
****/

#include <string>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <pcl_conversions/pcl_conversions.h>
#include <cv_bridge/cv_bridge.h>
#include <typeinfo>

namespace tabletop_segmentation {

class PointCloudRGBCombiner {
  typedef pcl::PointXYZRGB Point;

 private:
  ros::NodeHandle nh_;
  ros::Publisher color_pcl_pub_;
  ros::Subscriber image_sub_;

 public:

  PointCloudRGBCombiner(ros::NodeHandle nh) : nh_(nh)  {

    // std::string image_topic = nh_.resolveName(“img_in”);
    std::string image_topic = "/vrep/vrep_rgb_image";
    color_pcl_pub_ = nh_.advertise<sensor_msgs::PointCloud2>(nh_.resolveName("pcl_out"), 10);
    image_sub_ = nh_.subscribe(image_topic, 1, &PointCloudRGBCombiner::imageCb, this);

  }

  ~PointCloudRGBCombiner() {}

  void imageCb(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_color;
    std::vector<uint8_t> color_vect;
    ros::Time start_time = ros::Time::now();

    // std::string pcl_topic = nh_.resolveName(“pcl_in”);
    std::string pcl_topic = “/vrep/vrep_point_cloud”;

    ROS_INFO(“Waiting for point cloud2 and image”);

    while (ros::ok()) {
      sensor_msgs::PointCloud2::ConstPtr recent_cloud =
          ros::topic::waitForMessage<sensor_msgs::PointCloud2>(pcl_topic, nh_, ros::Duration(10.0));

      while (!recent_cloud) {
        ROS_ERROR("Waiting for point cloud2 and image");

        sensor_msgs::PointCloud2::ConstPtr recent_cloud =
            ros::topic::waitForMessage<sensor_msgs::PointCloud2>(pcl_topic, nh_, ros::Duration(3.0));
      }

      ROS_INFO_STREAM("pcl received after " << ros::Time::now() – start_time << " seconds. Start Combining…");

      merge(*const_cast<sensor_msgs::PointCloud2*>(recent_cloud.get()), msg->data);

      color_pcl_pub_.publish(*recent_cloud);
      cv_color.reset();
      recent_cloud.reset();
      color_vect.clear();
    }
  }


  void merge(sensor_msgs::PointCloud2 &cloud, const std::vector<uint8_t> &colors){
    size_t size = size_t(colors.size()/3);
    size_t col = size_t(640);
    size_t row = size_t(480);

    sensor_msgs::PointCloud2Iterator<uint8_t> iter_r(cloud, std::string("r"));
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_g(cloud, std::string("g"));
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_b(cloud, std::string("b"));

    int count =0 ;

    for (size_t j = 0; j < row; ++j ){
      for (size_t i =0; i < col; ++i, ++iter_r, ++iter_g, ++iter_b){
        count++;
        *iter_r = colors[3*(i+(479-j)*640)+0];
        *iter_g = colors[3*(i+(479-j)*640)+1];
        *iter_b = colors[3*(i+(479-j)*640)+2];
        //point cloud count from left to right, bottom to up while color image count from left to right, up to bottom
        //above conversion to force counting consistency of color with point cloud
      }
    }
  }

};
}

int main(int argc, char **argv){
  ros::init(argc, argv, "combine_depth_rgb");
  ros::NodeHandle nh;

  tabletop_segmentation::PointCloudRGBCombiner node(nh);
  ros::spin();
  return 0;
}
