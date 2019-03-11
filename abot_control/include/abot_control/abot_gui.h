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

namespace abot {
  class abot_gui : public QMainWindow
  {
    Q_OBJECT
    public:
      abot_gui(QWidget *parent = nullptr);
    private:
      Ui::MainWindow* ui; /* ui Subclass */
    signals:

    public slots:
  private slots:
  };
}

#endif // ABOT_GUI_H
