#include <QApplication>
#include <QWidget>
#include "abot_control/abot_node.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    abot::abot_node* node = new abot::abot_node(argc,argv);
//    QWidget window;
//    ros::init(argc, argv, "abot_control");
//    Abot = new abot::Abot_control(4);
//    Abot->setSendBuf(send_buf);
//    Abot->SerialSend(14);
//    abot::abot_gui gui(&window);
//    gui.show();
//    ros::NodeHandle actionServer;   /* actionSever句柄 */
//    AbotServer abotServer(actionServer,"abot_controller/follow_joint_trajectory",boost::bind(&Send2Serial,_1,&abotServer,Abot),false); /* 初始化AtionServer */
//    ROS_INFO("TrajectoryActionServer: Starting");
//    abotServer.start();   /* 启动server */
//    ros::spin();    /* 启动ros线程 */
    return app.exec();
}
