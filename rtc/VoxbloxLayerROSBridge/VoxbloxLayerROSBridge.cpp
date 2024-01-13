#include "VoxbloxLayerROSBridge.h"

VoxbloxLayerROSBridge::VoxbloxLayerROSBridge(RTC::Manager* manager):
  RTC::DataFlowComponentBase(manager),
  m_In_("voxbloxLayerIn", m_inData_),
  m_Out_("voxbloxLayerOut", m_outData_)
{
}

RTC::ReturnCode_t VoxbloxLayerROSBridge::onInitialize(){
  addInPort("voxbloxLayerIn", this->m_In_);
  addOutPort("voxbloxLayerOut", this->m_Out_);

  ros::NodeHandle pnh("~");
  sub_ = pnh.subscribe("input", 1, &VoxbloxLayerROSBridge::topicCb, this);
  pub_ = pnh.advertise<voxblox_msgs::Layer>("output", 1);

  return RTC::RTC_OK;
}

RTC::ReturnCode_t VoxbloxLayerROSBridge::onExecute(RTC::UniqueId ec_id){
  ros::spinOnce();

  if(this->m_In_.isNew()){
    this->m_In_.read();
    voxblox_msgs::Layer msg;
    msg.voxel_size = this->m_inData_.data.voxel_size;
    msg.voxels_per_side = this->m_inData_.data.voxels_per_side;
    msg.layer_type = this->m_inData_.data.layer_type;
    msg.action = this->m_inData_.data.action;
    msg.blocks.resize(this->m_inData_.data.blocks.length());
    for(int i=0;i<this->m_inData_.data.blocks.length();i++){
      msg.blocks[i].x_index = this->m_inData_.data.blocks[i].x_index;
      msg.blocks[i].y_index = this->m_inData_.data.blocks[i].y_index;
      msg.blocks[i].z_index = this->m_inData_.data.blocks[i].z_index;
      msg.blocks[i].data.resize(this->m_inData_.data.blocks[i].data.length());
      for(int j=0;j<this->m_inData_.data.blocks[i].data.length();j++){
	msg.blocks[i].data[j] = this->m_inData_.data.blocks[i].data[j];
      }
    }
    this->pub_.publish(msg);
  }
  return RTC::RTC_OK;
}

void VoxbloxLayerROSBridge::topicCb(voxblox_msgs::Layer::ConstPtr msg){
  ros::Time now = ros::Time::now();
  m_outData_.tm.sec = now.sec;
  m_outData_.tm.nsec = now.nsec;
  m_outData_.data.voxel_size = msg->voxel_size;
  m_outData_.data.voxels_per_side = msg->voxels_per_side;
  m_outData_.data.layer_type = msg->layer_type.c_str();
  m_outData_.data.action = msg->action;
  m_outData_.data.blocks.length(msg->blocks.size());
  for(int i=0;i<msg->blocks.size();i++){
    m_outData_.data.blocks[i].x_index = msg->blocks[i].x_index;
    m_outData_.data.blocks[i].y_index = msg->blocks[i].y_index;
    m_outData_.data.blocks[i].z_index = msg->blocks[i].z_index;
    m_outData_.data.blocks[i].data.length(msg->blocks[i].data.size());
    for(int j=0;j<msg->blocks[i].data.size();j++){
      m_outData_.data.blocks[i].data[j] = msg->blocks[i].data[j];
    }
  }
  m_Out_.write();
}

static const char* VoxbloxLayerROSBridge_spec[] = {
  "implementation_id", "VoxbloxLayerROSBridge",
  "type_name",         "VoxbloxLayerROSBridge",
  "description",       "VoxbloxLayerROSBridge component",
  "version",           "0.0",
  "vendor",            "Takume-Hiraoka",
  "category",          "example",
  "activity_type",     "DataFlowComponent",
  "max_instance",      "10",
  "language",          "C++",
  "lang_type",         "compile",
  ""
};

extern "C"{
    void VoxbloxLayerROSBridgeInit(RTC::Manager* manager) {
        RTC::Properties profile(VoxbloxLayerROSBridge_spec);
        manager->registerFactory(profile, RTC::Create<VoxbloxLayerROSBridge>, RTC::Delete<VoxbloxLayerROSBridge>);
    }
};
