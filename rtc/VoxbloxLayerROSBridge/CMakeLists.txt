add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

add_definitions(-Wno-deprecated)

find_package(catkin REQUIRED COMPONENTS
  rtmbuild
  roscpp
  voxblox_msgs
  )
find_package(PkgConfig REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}/.. # for /idl
  )
rtmbuild_add_executable(VoxbloxLayerROSBridgeComp VoxbloxLayerROSBridgeComp.cpp VoxbloxLayerROSBridge.cpp)
target_link_libraries(VoxbloxLayerROSBridgeComp ${catkin_LIBRARIES})
add_dependencies(VoxbloxLayerROSBridgeComp RTMBUILD_${PROJECT_NAME}_genrpc) # wait for rtmbuild_genidl
