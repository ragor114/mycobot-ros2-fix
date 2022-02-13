#include <chrono>
#include <fp/all.hpp>
#include <mycobot/command.hpp>
#include <mycobot/mycobot.hpp>
#include <thread>

int main() {
  auto mycobot = mycobot::make_mycobot();

  if (!mycobot) {
    fmt::print("{}\n", mycobot.error());
  }

  // power on
  {
    auto const result = mycobot->send(mycobot::power_on());
    if (!result) {
      fmt::print("{}\n", result.error());
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  // read joint angles
  {
    auto const joint_angles = mycobot->get_radians();
    fmt::print("get_radians: {}\n", joint_angles);
  }

  // move to origin
  {
    auto const result = mycobot->send_radians({0, 0, 0, 0, 0, 0}, 50);
    if (!result) {
      fmt::print("{}\n", result.error());
    }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  // read joint angles
  {
    auto const joint_angles = mycobot->get_radians();
    fmt::print("get_radians: {}\n", joint_angles);
  }

  // move a bit
  {
    auto const result =
        mycobot->send_radians({0.2, -0.2, 0.2, 0.2, -0.2, -0.2}, 50);
    if (!result) {
      fmt::print("{}\n", result.error());
    }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  // release all servos
  {
    auto const result = mycobot->send(mycobot::release_all_servos());
    if (!result) {
      fmt::print("{}\n", result.error());
    }
  }

  // power off
  {
    auto const result = mycobot->send(mycobot::power_off());
    if (!result) {
      fmt::print("{}\n", result.error());
    }
  }

  return 0;
}
