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
  ros::AsyncSpinner spin(1);
  initPlanningGroup("abot");
  spin.start();
}

void abot::abot_gui::initPlanningGroup(std::string name)
{
  PlanningGroup = new moveit::planning_interface::MoveGroupInterface(name);
}

void abot::abot_gui::on_pushButton_clicked()
{
  X = ui->doubleSpinBox_1->text().toDouble();
  Y = ui->doubleSpinBox_2->text().toDouble();
  Z = ui->doubleSpinBox_3->text().toDouble();
//  ui->textBrowser->insertPlainText(QString::number(X,10,5)+","+QString::number(Y,10,5)+","+QString::number(Z,10,5));
  geometry_msgs::PoseStamped pose1 = PlanningGroup->getCurrentPose();
  ui->textBrowser->insertPlainText(QString::number(pose1.pose.position.x,10,5)+","+QString::number(pose1.pose.position.y,10,5)+","+QString::number(pose1.pose.position.z,10,5)+","+QString::number(pose1.pose.orientation.w,10,5)+","+QString::number(pose1.pose.orientation.x,10,5)+","+QString::number(pose1.pose.orientation.y,10,5)+","+QString::number(pose1.pose.orientation.z,10,5));
  target_pose.position.x = 0.2;
  target_pose.position.y = 0;
  target_pose.position.z = 0.2;
  target_pose.orientation.w = 0.7071;
  target_pose.orientation.x = 0;
  target_pose.orientation.y = 0.7071;
  target_pose.orientation.z = 0;
  //PlanningGroup->setPoseTarget(target_pose);
  PlanningGroup->setRandomTarget();
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
