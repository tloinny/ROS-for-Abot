#include "abot_control/abot_control.h"

abot::Abot_control::Abot_control(int num)
{
    numOfJoints = num;
    try
    {
    //设置串口属性，并打开串口
        ros_serial.setPort("/dev/ttyUSB0");
        ros_serial.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ros_serial.setTimeout(to);
        ros_serial.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
    }
    if(ros_serial.isOpen())
    {
        ROS_INFO("Serial Port initialized");
    }
    else
    {
        ROS_INFO("Serial Port fails");
    }
}
