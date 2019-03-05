#include "abot_control/abot_control.h"
#include <actionlib/server/simple_action_server.h>
//#include "actionlib/server/action_server.h"
#include <control_msgs/FollowJointTrajectoryAction.h>
#include "math.h"

typedef actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> AbotServer;

static uint8_t send_buf[14];
static abot::Abot_control* Abot;

 /* AtionServer回调函数，在此接收MoveIt的goal，并且处理后发送给下位机 */
void Send2Serial(const control_msgs::FollowJointTrajectoryGoalConstPtr& a_goal, AbotServer* as, abot::Abot_control* robot)
{
    int numOfPoints = a_goal->trajectory.points.size(); /* get the number of points */
    //uint8_t send_buf[14];
    float lastDuration = 0.0;
        for (size_t i = 0; i < numOfPoints; i++)    /* 将goal做第一次处理，暂存到Js中 */
        {
			ROS_INFO("TIMES:%d",i);
            for (size_t n = 0; n < robot->numOfJoints; n++)
            {
                robot->abotJointstate.Js[n] = int(fabs(a_goal->trajectory.points[i].positions[n])*1000 + 0.5);
            }
            send_buf[0] = 255;
            send_buf[1] = 255;  /* 设置首尾标志位 */
            int n = 0;
            for (size_t i = 1; i < 13; i+=3,++n)  /* 将经过第一次处理的goal进行第二次加工，生成下位机能够识别的格式，并使用串口发送给下位机 */
            {
                send_buf[i] = robot->abotJointstate.Js[n]%254;
                send_buf[i+1] = robot->abotJointstate.Js[n]/254;
                send_buf[i+2] = 0;
                ROS_INFO("| %d | %d | %d | num:%d |",n,send_buf[i],send_buf[i+1],send_buf[i+1]*254+send_buf[i]);
            }
            if(i==numOfPoints-1)Abot->SerialSend(14);
        }
    as->setSucceeded(); /* 给client发送成功信号 */
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "abot_control");
    Abot = new abot::Abot_control(4);
    Abot->setSendBuf(send_buf);
    Abot->SerialSend(14);
    ros::NodeHandle actionServer;   /* actionSever句柄 */
    AbotServer abotServer(actionServer,"abot_controller/follow_joint_trajectory",boost::bind(&Send2Serial,_1,&abotServer,Abot),false); /* 初始化AtionServer */
    ROS_INFO("TrajectoryActionServer: Starting");
    abotServer.start();   /* 启动server */
    ros::spin();    /* 启动ros线程 */
    return 0;
}
