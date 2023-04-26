#include "task_list.h"
#include "ui_task_list.h"

task_list::task_list(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::task_list)
{
    ui->setupUi(this);
}
void task_list::change_task_id(int i){
    ui->task_id->setText(QString("任务%1").arg(i));
}
QString task_list::read_x(){
  return ui->x->text();
}
QString task_list::read_y(){
  return ui->y->text();
}
QString task_list::read_z(){
  return ui->z->text();
}
QString task_list::read_time(){
  return ui->time->text();
}
QString task_list::read_profit(){
  return ui->profit->text();
}

void task_list::write_message(QString x, QString y, QString z, QString time, QString profit){
    ui->x->setText(x);
    ui->y->setText(y);
    ui->z->setText(z);
    ui->time->setText(time);
    ui->profit->setText(profit);
}
task_list::~task_list()
{
    delete ui;
}
