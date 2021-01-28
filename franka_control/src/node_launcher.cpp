// Copyright (c) 2020 wngfra
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#include <array>
#include <memory>

#include <franka/robot.h>

#include <rclcpp/rclcpp.hpp>

#include "franka_control/FrankaStatePublisher.h"
#include "franka_control/SlidingControlServer.h"
#include "franka_control/TactileSubscriber.h"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto robot = std::make_shared<franka::Robot>(argv[1], getRealtimeConfig());
    RCLCPP_INFO(rclcpp::get_logger("Node_Launcher"), "Connected to robot@%s", argv[1]);

    auto O_F_ext_hat_K = std::make_shared<std::array<double, 6>>();
    auto position = std::make_shared<std::array<double, 3>>();
    auto quaternion = std::make_shared<std::array<double, 4>>();
    float *average_force = new float(0.0);

    auto publisher_handler = std::make_shared<franka_control::FrankaStatePublisher>(O_F_ext_hat_K, position, quaternion);
    auto control_server_handler = std::make_shared<franka_control::SlidingControlServer>(robot, average_force);
    // TODO: pointer error to fix
    // auto tactile_subscriber = std::make_shared<franka_control::TactileSubscriber>(average_force);
    
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(publisher_handler);
    executor.add_node(control_server_handler);
    // executor.add_node(tactile_subscriber);
    executor.spin();

    rclcpp::shutdown();

    return 0;
}