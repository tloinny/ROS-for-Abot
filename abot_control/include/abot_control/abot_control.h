/**
 *@title ROS for Abot
 * Copyright: Copyright (c) 2019 Abot [https://github.com/tloinny/ROS-for-Abot]
 *
 *@date on 2019-3-11
 *@author:tony-lin
 *@version 1.0.0
 *
 *@description: custom ROS robot control class
 */

#ifndef _ABOT_CONTROL_H_
#define _ABOT_CONTROL_H_

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <serial/serial.h>


struct AbotJointState
{
    int Js[4];
};

typedef struct AbotJointState AbotJointState;

namespace abot
{
    class Abot_control
    {
      public:
          Abot_control(int num);
          int numOfJoints;    /* 关节数目 */
          //ros::NodeHandle jointStatePublisher;    /* 关节状态发布者句柄 */
          AbotJointState abotJointstate;  /* 暂存关节状态 */
          serial::Serial ros_serial;  /* 跟下位机通讯的串口接口 */
          void SerialSend(int len);
          void setSendBuf(uint8_t* send_buf);
      private:
          void SerialInit();
          uint8_t* pSendBuf;
    };
}

#endif
