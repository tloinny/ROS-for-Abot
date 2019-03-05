#include "abot_control/abot_control.h"

abot::Abot_control::Abot_control(int num)
{
    numOfJoints = num;
    SerialInit();
}

void abot::Abot_control::SerialInit()
{
    try
    {
        //设置串口属性，并打开串口
        ros_serial.setPort("/dev/mcu_uart");
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
        ROS_ERROR_STREAM("Serial Port fails");
    }
}

void abot::Abot_control::setSendBuf(uint8_t* send_buf)
{
    pSendBuf = send_buf;
}

void abot::Abot_control::SerialSend(int len)
{
    if(ros_serial.isOpen())
    {
        ros_serial.write(pSendBuf,len);  /* 用串口发送出去 */
    }
}
