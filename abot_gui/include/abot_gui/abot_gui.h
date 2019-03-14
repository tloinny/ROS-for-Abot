/**
 *@title ROS for Abot
 * Copyright: Copyright (c) 2019 Abot [https://github.com/tloinny/ROS-for-Abot]
 *
 *@date on 2019-3-11
 *@author:tony-lin
 *@version 1.0.0
 *
 *@description: ROS gui class
 */

#ifndef ABOT_GUI_H
#define ABOT_GUI_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QWidget>
#include <moveit/move_group_interface/move_group_interface.h>
#include <QString>
#include <QDateTime>
#include <math.h>

#define pi 3.1415926

namespace abot {
  class abot_gui : public QMainWindow
  {
    Q_OBJECT
    public:
      abot_gui(QWidget *parent = nullptr);
      void initPlanningGroup(std::string name);
    private:
      moveit::planning_interface::MoveGroupInterface * PlanningGroup;
      geometry_msgs::Pose target_pose;
      Ui::MainWindow* ui; /* ui Subclass */

      bool showTimeStamp;

      double X,Y,Z;
    signals:

    public slots:
      void on_pushButton_clicked();
      void on_pushButton_1_clicked();
      void on_checkBox_stateChanged(int state);
      void on_checkBox_2_stateChanged(int state);
      void autoscrolling();
  };
}

#endif // ABOT_GUI_H
