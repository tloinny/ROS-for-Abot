//#include "abot_gui/abot_gui.h"
#include "/home/tloinny/catkin_ws/src/abot_ros/abot_gui/include/abot_gui/abot_gui.h"

abot::abot_gui::abot_gui(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  showTimeStamp = 0;
  int argc = 0; char **argv = NULL;
  ros::init (argc, argv, "abot_kinematics");
  ros::AsyncSpinner spin(10);
  initPlanningGroup("abot");
  PlanningGroup->setPlanningTime(10.0);
  spin.start();
}

void abot::abot_gui::initPlanningGroup(std::string name)
{
  PlanningGroup = new moveit::planning_interface::MoveGroupInterface(name);
}

void abot::abot_gui::on_pushButton_clicked()
{
  double theta = (3.14156*((ui->doubleSpinBox_4->text().toDouble())/180.0))/2;
  target_pose.position.x = (ui->doubleSpinBox_1->text().toDouble())/1000;
  target_pose.position.y = (ui->doubleSpinBox_2->text().toDouble())/1000;
  target_pose.position.z = (ui->doubleSpinBox_3->text().toDouble())/1000;
  double Alpha_sin = target_pose.position.y/(std::sqrt(std::pow(target_pose.position.x,2)+std::pow(target_pose.position.y,2)));
  double Alpha = std::asin(Alpha_sin);
  if(!(Alpha > -1.9195 && Alpha < 3.3155))
  {
    Alpha -= 2*pi;
  }
  target_pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(0, 1.5708, Alpha);;
//  target_pose.orientation.w = std::cos(theta);
//  target_pose.orientation.x = x_transform*std::sin(theta);
//  target_pose.orientation.y = y_transform*std::sin(theta);
//  target_pose.orientation.z = z_transform*std::sin(theta);
//  target_pose.orientation.w = std::cos(1.5705/2);
//  target_pose.orientation.x = 0;
//  target_pose.orientation.y = std::sin(1.5705/2);
//  target_pose.orientation.z = 0;
  PlanningGroup->setPoseTarget(target_pose);
  //PlanningGroup->setRandomTarget();
  //geometry_msgs::PoseStamped pos = PlanningGroup->getRandomPose("Link4");
  ui->textBrowser->insertPlainText(QString::number(Alpha_sin,10,5)+","+QString::number(target_pose.position.x,10,5)+","+QString::number(target_pose.position.y,10,5)+","+QString::number(target_pose.position.z,10,5)+","+QString::number(target_pose.orientation.w,10,5)+","+QString::number(target_pose.orientation.x,10,5)+","+QString::number(target_pose.orientation.y,10,5)+","+QString::number(target_pose.orientation.z,10,5)+"\n");
  //geometry_msgs::PoseStamped pos = PlanningGroup->getPoseTarget(PlanningGroup->getEndEffectorLink());
  //geometry_msgs::PoseStamped pos = PlanningGroup->getRandomPose(PlanningGroup->getEndEffectorLink());
  //ui->textBrowser->insertPlainText(QString::number(pos.pose.position.x,10,5)+","+QString::number(pos.pose.position.y,10,5)+","+QString::number(pos.pose.position.z,10,5)+","+QString::number(pos.pose.orientation.w,10,5)+","+QString::number(pos.pose.orientation.x,10,5)+","+QString::number(pos.pose.orientation.y,10,5)+","+QString::number(pos.pose.orientation.z,10,5)+"\n");
  //PlanningGroup->setPoseTarget(pos);
  PlanningGroup->asyncMove();
  if(showTimeStamp == 1)
  {
    QDateTime current_date_time = QDateTime::currentDateTime();
    ui->textBrowser->insertPlainText(current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz")+"\n");
  }
  else
  {
    ui->textBrowser->insertPlainText("\n");
  }
}


void abot::abot_gui::on_pushButton_1_clicked()
{
  ui->textBrowser->setPlainText("");
}

void abot::abot_gui::on_checkBox_stateChanged(int state)
{
  if(state == 2)
  {
    showTimeStamp = 1;
  }else
  {
    showTimeStamp = 0;
  }
}

void abot::abot_gui::on_checkBox_2_stateChanged(int state)
{
  if(state == 2)
  {
    connect(ui->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(autoscrolling()));
  }else
  {
    disconnect(ui->textBrowser,SIGNAL(cursorPositionChanged()),this,SLOT(autoscrolling()));
  }
}

void abot::abot_gui::autoscrolling()
{
  QTextCursor cursor =  ui->textBrowser->textCursor();
  cursor.movePosition(QTextCursor::End);
  ui->textBrowser->setTextCursor(cursor);
}
