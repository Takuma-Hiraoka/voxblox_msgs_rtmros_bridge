#ifndef VoxbloxLayerROSBridge_H
#define VoxbloxLayerROSBridge_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/DataOutPort.h>
#include <rtm/DataInPort.h>

#include <ros/ros.h>
#include <voxblox_msgs_rtmros_bridge/idl/Voxblox.hh>
#include <voxblox_msgs/Layer.h>

class VoxbloxLayerROSBridge : public RTC::DataFlowComponentBase{
protected:
  ros::NodeHandle nh;

  voxblox_msgs_rtmros_bridge::TimedVoxbloxLayer m_inData_;
  RTC::InPort<voxblox_msgs_rtmros_bridge::TimedVoxbloxLayer> m_In_;
  ros::Publisher pub_;

  voxblox_msgs_rtmros_bridge::TimedVoxbloxLayer m_outData_;
  RTC::OutPort<voxblox_msgs_rtmros_bridge::TimedVoxbloxLayer> m_Out_;
  ros::Subscriber sub_;

  void topicCb(voxblox_msgs::Layer::ConstPtr msg);

public:
  VoxbloxLayerROSBridge(RTC::Manager* manager);
  virtual RTC::ReturnCode_t onInitialize();
  virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

};

extern "C"
{
  void VoxbloxLayerROSBridgeInit(RTC::Manager* manager);
};

#endif // VoxbloxLayerROSBridge_H
