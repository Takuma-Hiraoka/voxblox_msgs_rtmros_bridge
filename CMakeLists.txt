cmake_minimum_required(VERSION 3.0.2)
project(voxblox_msgs_rtmros_bridge)

add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

cmake_policy(SET CMP0046 OLD)

find_package(catkin REQUIRED COMPONENTS
  rtmbuild
  roscpp
  )

rtmbuild_init()

catkin_package(
  LIBRARIES VoxbloxSkel VoxbloxStub
)

rtmbuild_genidl()

add_subdirectory(rtc)
