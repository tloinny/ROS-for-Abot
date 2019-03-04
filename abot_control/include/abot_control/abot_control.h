#ifndef _ABOT_CONTROL_H_
#define _ABOT_CONTROL_H_

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <serial/serial.h>

struct AbotJointState
{
    int Js[4];
    float duration;
};

typedef struct AbotJointState AbotJointState;

namespace abot
{
    class Abot_control
    {
    public:
        Abot_control(int num);
        int numOfJoints;    /* 关节数目 */
        ros::NodeHandle jointStatePublisher;    /* 关节状态发布者句柄 */
        AbotJointState abotJointstate;  /* 暂存关节状态 */
        serial::Serial ros_serial;  /* 跟下位机通讯的串口接口 */
    private:
    };
}

#endif
