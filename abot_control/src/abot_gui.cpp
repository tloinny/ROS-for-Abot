#include "abot_control/abot_gui.h"

abot::abot_gui::abot_gui(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}
