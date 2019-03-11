#include <QApplication>
#include <QWidget>
#include "abot_gui/abot_gui.h"

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);
  QWidget window;
  abot::abot_gui gui(&window);
  gui.show();
  return app.exec();
}
