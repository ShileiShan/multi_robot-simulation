#include "position.h"
#include "ui_position.h"
#include <QDebug>
int g_a = 1;    //全局变量
position::position(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::position)
{
    ui->setupUi(this);
}

position::~position()
{
    delete ui;
}

void position::changeLabel(QString s,int a)
{

    ui->label->setText(QString(s+"机器人%1位置").arg(a));
}

//读取位置信息
QString position::Read_x()
{
    return ui->x->text();
}

QString position::Read_y()
{
    return ui->y->text();
}

QString position::Read_z()
{
    return ui->z->text();
}

//写入位置信息
void position::Write_xyz(QString x,QString y,QString z)
{
    ui->x->setText(x);
    ui->y->setText(y);
    ui->z->setText(z);
}

void position::disable_add_robot()
{
    ui->add_robot->setDisabled(true);
}

//void position::delete_robot()
//{
//    QString str=ui->label->text();
//    str=str.mid(5,1);
//    qDebug() << str;
//}

void position::on_add_robot_clicked()
{
    QString str = ui->label->text();
    QString pub_robot = "{";
    QString name = str.mid(0,2);
    qDebug() << name;
    if(name == "轮式"){
        QString bash = "roslaunch test_wheel wheel_robot.launch";
        QString amcl_robot="roslaunch robot_navigation amcl_robot.launch";
        QString move_base="roslaunch robot_navigation move_base_0.launch";
        QString num;
        num=str.mid(5,1);
        QString x=Read_x();
        QString y=Read_y();
        QString z=Read_z();
        bash = bash+" ns:="+"robot"+num+" x:="+x+" y:="+y+" z:="+z;
        amcl_robot=amcl_robot+" ns:="+"robot"+num+" initial_pose_x:="+x+" initial_pose_y:="+y;
        move_base=move_base+" ns:="+"robot"+num+" num:="+num;
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 0, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(num);
        cmd(bash);
        cmd(amcl_robot);
        cmd(move_base);
        cmd(pub_robot);
    }
    else if(name == "履带"){
        QString bash = "roslaunch test_crawler crawler_robot.launch";
        QString amcl_robot="roslaunch robot_navigation amcl_robot.launch";
        QString move_base="roslaunch robot_navigation move_base_0.launch";
        QString num;
        num = "1" + str.mid(5,1);
        QString x=Read_x();
        QString y=Read_y();
        QString z=Read_z();
        bash = bash+" ns:="+"robot"+num+" x:="+x+" y:="+y+" z:="+z;
        amcl_robot=amcl_robot+" ns:="+"robot"+num+" initial_pose_x:="+x+" initial_pose_y:="+y;
        move_base=move_base+" ns:="+"robot"+num+" num:="+num;
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 1, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(num);
        cmd(bash);
        cmd(amcl_robot);
        cmd(move_base);
        cmd(pub_robot);
    }
    if(name == "无人"){
        QString robot = "roslaunch rotors_gazebo drone.launch";
        QString pub_robot = "{";
        QString num;
        QString x=Read_x();
        QString y=Read_y();
        QString z=Read_z();
        num = "2" + str.mid(6,1);
        robot = robot+" ns:="+"robot"+num+" x:="+x+" y:="+y+" z:="+z;
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 2, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(num);
        cmd(robot);
        cmd(pub_robot);
    }
    ui->add_robot->setDisabled(true);
    ui->x->setDisabled(true);
    ui->y->setDisabled(true);
    ui->z->setDisabled(true);
}

void position::on_delete_robot_clicked()
{
    QString str = ui->label->text();
    QString name = str.mid(0,2);
    qDebug() << name;
    if(name == "轮式"){
        QString num;
        num=str.mid(5,1);
        QString delete_robot=QString("rosservice call /gazebo/delete_model \"model_name: 'robot%1'\"").arg(num);
        cmd(delete_robot);
    }
    else if(name == "履带"){
        QString num;
        num="1" + str.mid(5,1);
        qDebug() << num;
        QString delete_robot=QString("rosservice call /gazebo/delete_model \"model_name: 'robot%1'\"").arg(num);
        cmd(delete_robot);
    }
    else if(name == "无人"){
        QString num;
        num="2" + str.mid(6,1);
        //qDebug() << num;
        QString delete_robot=QString("rosservice call /gazebo/delete_model \"model_name: 'robot%1'\"").arg(num);
        cmd(delete_robot);
    }
    ui->delete_robot->setDisabled(true);
}
void position::disable_change_position(){
    ui->x->setDisabled(true);
    ui->y->setDisabled(true);
    ui->z->setDisabled(true);
}

void position::cmd(QString bash){
    quick_cmd = new QProcess;
    quick_cmd->start("bash");
    //bash = "source ~/catkin_wq/devel/setup.bash \n"+bash;
    qDebug() << bash;
    quick_cmd->write(bash.toLocal8Bit()+'\n');
}
