#include <QApplication>
#include <QWidget>
#include "abot_control/abot_node.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    abot::abot_node* node = new abot::abot_node(argc,argv);
    return app.exec();
}
