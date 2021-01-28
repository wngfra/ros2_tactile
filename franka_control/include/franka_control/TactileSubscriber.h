// Copyright (c) 2020 wngfra
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#pragma once

#include <array>
#include <memory>
#include <rclcpp/rclcpp.hpp>

#include "tactile_interfaces/msg/tactile_signal.hpp"

using std::placeholders::_1;

using namespace std::chrono_literals;

namespace franka_control
{
    class TactileSubscriber : public rclcpp::Node
    {
    public:
        TactileSubscriber(float *average_force) : Node("tactiel_signal_subscriber")
        {
            subscription_ = this->create_subscription<tactile_interfaces::msg::TactileSignal>("tactile_signals", 10, std::bind(&TactileSubscriber::topic_callback, this, _1));

            average_force = average_force_;
        }

    private:
        void topic_callback(const tactile_interfaces::msg::TactileSignal::SharedPtr msg);

        rclcpp::Subscription<tactile_interfaces::msg::TactileSignal>::SharedPtr subscription_;
        std::array<int32_t, 16> data_array_;

        float *average_force_;
    };
} // namespace franka_control