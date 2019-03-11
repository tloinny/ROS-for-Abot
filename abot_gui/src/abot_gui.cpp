#include "abot_gui/abot_gui.h"

abot::abot_gui::abot_gui(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  showTimeStamp = 0;
}


void abot::abot_gui::on_pushButton_clicked()
{
  X = ui->doubleSpinBox_1->text().toDouble();
  Y = ui->doubleSpinBox_2->text().toDouble();
  Z = ui->doubleSpinBox_3->text().toDouble();
  ui->textBrowser->insertPlainText(QString::number(X,10,5)+","+QString::number(Y,10,5)+","+QString::number(Z,10,5));
  if(showTimeStamp == 1)
  {
    QDateTime current_date_time = QDateTime::currentDateTime();
    ui->textBrowser->insertPlainText(current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz")+"\n");
  }else {
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
