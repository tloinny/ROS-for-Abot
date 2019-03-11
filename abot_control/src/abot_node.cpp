#include "abot_control/abot_node.h"

static uint8_t send_buf[14];

abot::abot_node::abot_node(int argc, char** argv):
  init_argc(argc),
  init_argv(argv),
  Abot_controller(new abot::Abot_control(4))
{
  /* init ros */
  ros::init(init_argc,init_argv,"abot");
  if(!ros::master::check())   /* check ros master */
  {
    ROS_INFO("NO MASTER");
  }
  ros::start();

  Abot_controller->setSendBuf(send_buf);  /* config send_buf for Abot_controller */

  ros::NodeHandle actionServer;
  AbotServer abotServer(actionServer,"abot_controller/follow_joint_trajectory",boost::bind(&abot_node::Send2Serial,this,_1,&abotServer),false);
  abotServer.start();
  ROS_INFO("TrajectoryActionServer: Starting");
  ros::spin();
}

/**
 * @function
 * AtionServer回调函数，在此接收MoveIt的goal，并且处理后发送给下位机
 * @param
 *       a_goal
 *       as
 */
void abot::abot_node::Send2Serial(const control_msgs::FollowJointTrajectoryGoalConstPtr& a_goal, AbotServer* as/*, abot::Abot_control* robot*/)
{
   int numOfPoints = a_goal->trajectory.points.size(); /* get the number of points */
       for (size_t i = 0; i < numOfPoints; i++)    /* 将goal做第一次处理，暂存到Js中 */
       {
           ROS_INFO("TIMES:%d",i);
           for (size_t n = 0; n < Abot_controller->numOfJoints; n++)
           {
               Abot_controller->abotJointstate.Js[n] = int((a_goal->trajectory.points[i].positions[n])*1000 + 0.5);
                ROS_INFO("yaw%d:%d",n,Abot_controller->abotJointstate.Js[n]);
               switch (n)
               {
                 case 0:
                   Abot_controller->abotJointstate.Js[n] = 3315 - Abot_controller->abotJointstate.Js[n];
                   break;
                 case 1:
                 case 3:
                   Abot_controller->abotJointstate.Js[n] = 1570 - Abot_controller->abotJointstate.Js[n];
                   break;
                 case 2:
                   Abot_controller->abotJointstate.Js[n] = 2268 - Abot_controller->abotJointstate.Js[n];
                   break;
                 default:
                   break;
               }
           }
           send_buf[0] = 255;
           send_buf[13] = 255;  /* 设置首尾标志位 */
           int n = 0;
           for (size_t i = 1; i < 13; i+=3,++n)  /* 将经过第一次处理的goal进行第二次加工，生成下位机能够识别的格式，并使用串口发送给下位机 */
           {
               send_buf[i] = Abot_controller->abotJointstate.Js[n]%254;
               send_buf[i+1] = Abot_controller->abotJointstate.Js[n]/254;
               send_buf[i+2] = 0;
               ROS_INFO("| Joint:%1d | %3d | %3d | rad:%4d |",n,send_buf[i],send_buf[i+1],send_buf[i+1]*254+send_buf[i]);
           }
           if(i==numOfPoints-1)Abot_controller->SerialSend(14);
       }
   as->setSucceeded(); /* 给client发送成功信号 */
}
