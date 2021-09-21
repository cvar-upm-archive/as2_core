// "Copyright [year] <Copyright Owner>"

#ifndef AEROSTACK2_AERIAL_PLATFORM_HPP_
#define AEROSTACK2_AERIAL_PLATFORM_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "node.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/publisher_options.hpp"

#include "aerostack2_msgs/msg/platform_control_mode.hpp"
#include "aerostack2_msgs/msg/platform_status.hpp"
#include "aerostack2_msgs/srv/set_platform_control_mode.hpp"
#include "aerostack2_core/naming.hpp"

#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"



namespace aerostack2
{
class AerialPlatform : public aerostack2::Node
{
public:
  AerialPlatform();
  
  //TODO
  virtual bool ownConfigureSensors()= 0;
  virtual bool ownPublishSensorData()= 0;

  virtual bool ownSetArmingState(bool state)= 0;
  virtual bool ownSetOffboardControl(bool offboard) = 0;
  virtual aerostack2_msgs::msg::PlatformStatus ownSetPlatformStatus() = 0;
  
  virtual bool ownSetPlatformControlMode(const aerostack2_msgs::msg::PlatformControlMode & msg) = 0;
  virtual bool ownSendCommand(const aerostack2_msgs::msg::PlatformControlMode & msg) = 0;

protected:

  bool configureSensors();
  bool readSensors();
  bool publishSensorData();

  bool setArmingState(bool state);
  bool setOffboardControl(bool offboard);
  aerostack2_msgs::msg::PlatformStatus setPlatformStatus();

  bool setPlatformControlMode(const aerostack2_msgs::msg::PlatformControlMode & msg);
  bool sendCommand(const aerostack2_msgs::msg::PlatformControlMode & msg);

  aerostack2::names::global_topics::actuator_commands::POSE_COMMAND_TYPE  command_pose_msg_;
  aerostack2::names::global_topics::actuator_commands::TWIST_COMMAND_TYPE command_twist_msg_;
  



private:
  

  aerostack2_msgs::msg::PlatformStatus platform_status_;

  bool sensors_configured_ = false;
  bool control_mode_settled_ = false;

  rclcpp::Service<aerostack2_msgs::srv::SetPlatformControlMode>::SharedPtr set_platform_mode_srv_;
  void setPlatformControlModeSrvCall( const std::shared_ptr<aerostack2_msgs::srv::SetPlatformControlMode::Request> request,
                                            std::shared_ptr<aerostack2_msgs::srv::SetPlatformControlMode::Response> response);

  // bool setArmingStateSrvCall(const std::shared_ptr<std_msgs::msg::Bool> request,);
  
  rclcpp::Publisher<aerostack2_msgs::msg::PlatformStatus>::SharedPtr platform_status_pub_;

  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_command_sub_;
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr twist_command_sub_;
  

  void publishPlatformStatus();

  

}; //class AerialPlatform

};      // namespace aerostack2
#endif  //AEROSTACK2_NODE_HPP_