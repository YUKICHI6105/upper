#include <can_plugins2/msg/frame.hpp>
#include <robomas_plugins/msg/robomas_frame.hpp>
#include <robomas_plugins/msg/robomas_target.hpp>
#include <rclcpp/rclcpp.hpp>

namespace robomas
{
    static std::unique_ptr<robomas_plugins::msg::RobomasTarget> get_target(const float target_data)
    {
        auto target = std::make_unique<robomas_plugins::msg::RobomasTarget>();
        target->target = target_data;
        return target;
    }

    static std::unique_ptr<robomas_plugins::msg::RobomasFrame> get_upper_frame(const uint16_t id) 
    {
        auto frame = std::make_unique<robomas_plugins::msg::RobomasFrame>();
        frame->mode = 4;
        frame->motor = id;
        frame->c620 = 0;
        frame->temp = 50;
        frame->velkp = 0.25;
        frame->velki = 9;
        frame->poskp = 0.5;
        frame->stable_pos_limit_vel = 25;
        return frame;
    }
}

