#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <robomas_plugins/msg/robomas_frame.hpp>
#include <robomas_plugins/msg/robomas_target.hpp>
#include <upper/robomas_utils.hpp>

class UpperNode : public rclcpp::Node
{
  private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasFrame>::SharedPtr frame_pub_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasTarget>::SharedPtr target_pub1_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasTarget>::SharedPtr target_pub2_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasTarget>::SharedPtr target_pub3_;
    rclcpp::Publisher<robomas_plugins::msg::RobomasTarget>::SharedPtr target_pub4_;
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg);
    uint8_t prebutton = 0;
    uint8_t togglebutton = 0;
    float position = 0; 
  public:
    UpperNode() : Node("upper_node")
    {
      sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&UpperNode::joy_callback, this, std::placeholders::_1));
      frame_pub_ = this->create_publisher<robomas_plugins::msg::RobomasFrame>("robomas_frame", 10);
      target_pub1_ = this->create_publisher<robomas_plugins::msg::RobomasTarget>("robomas_target1", 10);
      target_pub2_ = this->create_publisher<robomas_plugins::msg::RobomasTarget>("robomas_target2", 10);
      target_pub3_ = this->create_publisher<robomas_plugins::msg::RobomasTarget>("robomas_target3", 10);
      target_pub4_ = this->create_publisher<robomas_plugins::msg::RobomasTarget>("robomas_target4", 10);
    }
};

void UpperNode::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg){
  if (msg->buttons[togglebutton] == 1)
  {
    if (prebutton == 0)
    {
      if (position == 0)
      {
        position = 2300;
      }
      else
      {
        position = 0;
      }
      target_pub1_->publish(robomas::get_target(position));
      prebutton = 1;
    }
  }else{
    if(prebutton==1){
      prebutton = 0;
    }
  }
  if(msg->buttons[6] == 1){
    frame_pub_->publish(robomas::get_upper_frame(0));
  }
}

int main(int argc, char *argv[])
{
  // printf("hello world odom_check package\n");
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<UpperNode>());
  rclcpp::shutdown();
  return 0;
}