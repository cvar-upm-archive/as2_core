// "Copyright [year] <Copyright Owner>"

#ifndef AEROSTACK2_NODE_HPP_
#define AEROSTACK2_NODE_HPP_

#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "rclcpp/publisher.hpp"
#include "rclcpp/publisher_options.hpp"

#include "naming.hpp"

namespace aerostack2
{
class Node : public rclcpp::Node
{
public:
  Node(const std::string& name) : rclcpp::Node(name){};
  std::string get_drone_id(){return "drone0";};
  
  std::string generate_local_topic_name(const std::string& name){return "/"+ this->get_drone_id() + "/"+ this->get_name()+"/"+ name;};
  std::string generate_topic_name(const std::string& name){return "/"+ this->get_drone_id() + "/"+ name;};
};
}  // namespace aerostack2

#endif  //AEROSTACK2_NODE_HPP_