#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "position.h"
#include "task_list.h"
#include <QScrollArea>
#include <QLayout>
#include <QWidget>
#include <QTabWidget>
#include <QMessageBox>
#include <QtGui>
#include <QTreeWidgetItem>
#include <QCheckBox>
#include <QProcess>
#include <vector>
#include <QMetaType>
#include <memory>

extern int g_a;
MainWindow::MainWindow(int argc, char** argv, shared_ptr<QProcess>& p1, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),qnode(argc,argv)
{
    ui->setupUi(this);
    InitUi();
    qRegisterMetaType<QVector<int>>("QVector<int>");
    QPalette red;
    red.setColor(QPalette::WindowText,Qt::red);
    ui->title1->setPalette(red);
    ui->title2->setPalette(red);
    ReadSettings();
    //ui->one_robot_task->addItems(qnode.task_2_list);
    //ui->xiaohui->setPixmap(QPixmap(":/Image/xiaohui.jpg"));
    ui->Tab_1->setCurrentIndex(0);
    ui->Tab_2->setCurrentIndex(0);
    ui->treeWidget_quick_cmd->setHeaderLabels(QStringList()<<"key"<<"values");
    ui->treeWidget_quick_cmd->setHeaderHidden(true);

    ui->one_robot_view->setModel(qnode.loggingModel2());
    ui->muti_robot_view->setModel(qnode.loggingModel1());

    connect(&qnode, SIGNAL(loggingUpdated2()), this, SLOT(updateLoggingView2()));
    connect(&qnode, SIGNAL(loggingUpdated1()), this, SLOT(updateLoggingView1()));

    connect(ui->Tab_1,SIGNAL(currentChanged(int)),this,SLOT(slot_tab_manage_currentChanged(int)));
    connect(ui->Wheel_Num,SIGNAL(textChanged(QString)),this,SLOT(Wheel_Init(QString)));
    connect(ui->Track_Num,SIGNAL(textChanged(QString)),this,SLOT(Track_Init(QString)));
    connect(ui->Drone_Num,SIGNAL(textChanged(QString)),this,SLOT(Drone_Init(QString)));
    connect(ui->task_num,SIGNAL(textChanged(QString)),this,SLOT(init_task(QString)));
    connect(ui->add_wheel,SIGNAL(clicked()),this,SLOT(add_addition_wheel()));
    connect(ui->add_crawler,SIGNAL(clicked()),this,SLOT(add_addition_track()));
    connect(ui->add_drone,SIGNAL(clicked()),this,SLOT(add_addition_drone()));
    connect(ui->Num_Confirm,SIGNAL(clicked()),this,SLOT(robot_gazebo()));
    connect(ui->confirm_task_num,SIGNAL(clicked()),this,SLOT(confirm_task()));
    //connect(ui->connect,SIGNAL(clicked),Wheel,SLOT(delete_robot()));
    connect(ui->quick_cmd_add_btn,SIGNAL(clicked()),this,SLOT(quick_cmd_add()));
    connect(ui->quick_cmd_remove_btn,SIGNAL(clicked()),this,SLOT(quick_cmd_remove()));
    connect(ui->connect,SIGNAL(clicked()),this,SLOT(button_connect_clicked()));

    newp1 = p1;

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*****************************************************************************
** 实现ROS master链接检测
*****************************************************************************/
void MainWindow::button_connect_clicked() {
    if ( ! qnode.init(ui->edit_master->text().toStdString(),ui->edit_host->text().toStdString()) )
        {
            showNoMasterMessage();
        }
   else {
            ui->connect->setEnabled(false);
            ui->edit_master->setReadOnly(true);
            ui->edit_host->setReadOnly(true);
            ui->connect_state->setText("已连接");
        }
}

void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("未找到ros master.");
    msgBox.exec();
    //close();
}

void MainWindow::showRobotMessage() {
    QMessageBox msgBox;
    msgBox.setText("该机器人数量达到上线.");
    msgBox.exec();
    //close();
}
void MainWindow::updateLoggingView2() {
        ui->one_robot_view->scrollToBottom();
}
void MainWindow::updateLoggingView1() {
        ui->muti_robot_view->scrollToBottom();
}
/*****************************************************************************
** 实现初始化
*****************************************************************************/

//左工具栏索引改变
void MainWindow::slot_tab_manage_currentChanged(int index)
{
    switch (index) {
    case 0:
        ui->Tab_2->setCurrentIndex(0);
        break;
    case 1:
        ui->Tab_2->setCurrentIndex(1);
        break;
    case 2:
        ui->Tab_2->setCurrentIndex(2);
        break;
    case 3:
        ui->Tab_2->setCurrentIndex(3);
        break;
    case 4:
        ui->Tab_2->setCurrentIndex(4);
        break;
    }
}
void MainWindow::InitUi(){
}
//记录位置信息
vector<vector<QString>> MainWindow::remember_task(){
    vector<vector<QString>> r_t;
    vector<QString> row(5);
    for(int i=0;i<20;i++){
        row[0] = task[i].read_x();
        row[1] = task[i].read_y();
        row[2] = task[i].read_z();
        row[3] = task[i].read_time();
        row[4] = task[i].read_profit();
        r_t.push_back(row);
    }
    return r_t;
}

vector<vector<QString>> MainWindow::remember_position(int a)
{
    switch(a){
        case 1:
        {
            vector<vector<QString>> r_p;
            vector<QString> row(3);
            for(int i=0;i<10;i++){
                row[0]=Wheel[i].Read_x();
                row[1]=Wheel[i].Read_y();
                row[2]=Wheel[i].Read_z();
                r_p.push_back(row);
            }
            return r_p;
            break;
        }
        case 2:
        {
            vector<vector<QString>> r_p;
            vector<QString> row(3);
            for(int i=0;i<10;i++){
                row[0]=Track[i].Read_x();
                row[1]=Track[i].Read_y();
                row[2]=Track[i].Read_z();
                r_p.push_back(row);
            }
            return r_p;
            break;
        }
        case 3:
        {
            vector<vector<QString>> r_p;
            vector<QString> row(3);
            for(int i=0;i<5;i++){
                row[0]=Drone[i].Read_x();
                row[1]=Drone[i].Read_y();
                row[2]=Drone[i].Read_z();
                r_p.push_back(row);
            }
            return r_p;
            break;
        }
        default:
        {
             break;
        }
    }
    return {{}};
}

//写入位置信息
void MainWindow::load_task(vector<vector<QString>> r_t){
    for(int i=0; i<20; i++){
        task[i].write_message(r_t[i][0],r_t[i][1],r_t[i][2],r_t[i][3],r_t[i][4]);
    }
}
void MainWindow::load_position(int a,vector<vector<QString>> r_p){
    switch(a){
        case 1:
        {
            for(int i=0;i<10;i++){
                Wheel[i].Write_xyz(r_p[i][0],r_p[i][1],r_p[i][2]);
            }
            break;
        }
        case 2:
        {
            for(int i=0;i<10;i++){
                Track[i].Write_xyz(r_p[i][0],r_p[i][1],r_p[i][2]);
            }
            break;
        }
        case 3:
        {
            for(int i=0;i<5;i++){
                Drone[i].Write_xyz(r_p[i][0],r_p[i][1],r_p[i][2]);
            }
            break;
        }
        default:
        {
             break;
        }
    }

}
//用来加入机器人
void MainWindow::Wheel_Init(QString s){
    //vector<vector<QString>> r_p=remember_position(1);
    if(ui->scrollAreaWidgetContents_2->layout()){
        delete ui->scrollAreaWidgetContents_2->layout();
        delete [] Wheel;
    }

    int number = 0;
    try {
        number = s.toInt();
        if(number > 10 || number < 0){
            throw " ";
        }

    } catch (...) {
        qDebug()<<"Invalid Input";
        return ;
    }


    Wheel= new position[10];
    QVBoxLayout *layout1 = new QVBoxLayout();
    for(int i = 0; i < number; i++){
        Wheel[i].changeLabel("轮式", i);
        layout1->addWidget(&Wheel[i]);
    }
    ui->scrollAreaWidgetContents_2->setLayout(layout1);
    //load_position(1,r_p);
}

void MainWindow::Track_Init(QString s){
//    vector<vector<QString>> r_p=remember_position(2);
    if(ui->scrollAreaWidgetContents_3->layout()){
        delete ui->scrollAreaWidgetContents_3->layout();
        delete [] Track;
    }

    int number = 0;
    try {
        number = s.toInt();
        if(number > 10 || number < 0){
            throw " ";
        }

    } catch (...) {
        qDebug()<<"Invalid Input";
        return ;
    }

    Track = new position[10];
    QVBoxLayout *layout1 = new QVBoxLayout();
    for(int i = 0; i < number; i++){
        Track[i].changeLabel("履带", i);
        layout1->addWidget(&Track[i]);
    }
    ui->scrollAreaWidgetContents_3->setLayout(layout1);
//    load_position(2,r_p);
}


void MainWindow::Drone_Init(QString s){
//    vector<vector<QString>> r_p=remember_position(3);

    if(ui->scrollAreaWidgetContents_4->layout()){
        delete ui->scrollAreaWidgetContents_4->layout();
        delete [] Drone;
    }
    int number = 0;

    try {
        number = s.toInt();
        if(number > 5 || number < 0){
            throw " ";
        }

    } catch (...) {
        qDebug()<<"Invalid Input";
        return ;
    }

    Drone = new position[5];
    QVBoxLayout *layout1 = new QVBoxLayout();
    for(int i = 0; i < number; i++){
        Drone[i].changeLabel("无人机", i);
        layout1->addWidget(&Drone[i]);
    }
    ui->scrollAreaWidgetContents_4->setLayout(layout1);
//    load_position(3,r_p);
}
//添加额外机器人
void MainWindow::add_addition_wheel(){
    addition_wheel_num += 1;
    int total_num = addition_wheel_num + wheel_num;
    if(total_num <= 10){
        Wheel[total_num - 1].changeLabel("轮式", total_num - 1);
        ui->scrollAreaWidgetContents_2->layout()->addWidget(&Wheel[total_num - 1]);
        for(int i=0;i<wheel_num;i++){
            Wheel[i].disable_change_position();
            Wheel[i].disable_add_robot();
        }
    }
    else{
        showRobotMessage();
    }
}

void MainWindow::add_addition_track(){
    addition_track_num += 1;
    int total_num = addition_track_num + track_num;
    if(total_num <= 10){
        Track[total_num - 1].changeLabel("履带", total_num-1);
        ui->scrollAreaWidgetContents_3->layout()->addWidget(&Track[total_num - 1]);
        for(int i = 0; i < track_num; i++){
            Track[i].disable_change_position();
            Track[i].disable_add_robot();
        }
    }
    else{
        showRobotMessage();
    }
}
void MainWindow::add_addition_drone(){
    addition_drone_num += 1;
    int total_num = addition_drone_num + drone_num;
    if(total_num <= 5){
        Drone[total_num - 1].changeLabel("无人机", total_num-1);
        ui->scrollAreaWidgetContents_4->layout()->addWidget(&Drone[total_num - 1]);
        for(int i = 0; i < drone_num; i++){
            Drone[i].disable_change_position();
            Drone[i].disable_add_robot();
        }
    }
    else{
        showRobotMessage();
    }
}


//命令行函数
//void MainWindow::cmd(QString bash){
//    quick_cmd = new QProcess;
//    quick_cmd->start("bash");
//    //bash = "source ~/catkin_wq/devel/setup.bash \n"+bash;
//    qDebug() << bash.toLocal8Bit()+'\n';
//    quick_cmd->write(bash.toLocal8Bit()+'\n');
//    //quick_cmd->waitForFinished();
//    //connect(quick_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(cmd_output()));
//    //connect(quick_cmd,SIGNAL(readyReadStandardError()),this,SLOT(cmd_error_output()));
//}
// 智能指针
void MainWindow::cmd(QString bash){

    quick_cmd = new QProcess;
    quick_cmd->start("bash");
    //bash = "source ~/catkin_wq/devel/setup.bash \n"+bash;
    qDebug() << bash.toLocal8Bit()+'\n';
    quick_cmd->write(bash.toLocal8Bit()+'\n');
    //quick_cmd->waitForFinished();
    //connect(quick_cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(cmd_output()));
    //connect(quick_cmd,SIGNAL(readyReadStandardError()),this,SLOT(cmd_error_output()));
}
/*****************************************************************************
** 实现任务的添加
*****************************************************************************/
void MainWindow::init_task(QString s){
    vector<vector<QString>> r_t = remember_task();
    if(ui->task_list->layout()){
        delete ui->task_list->layout();
        delete [] task;
    }
    int number = s.toInt();
    task = new task_list[20];
    load_task(r_t);
    QVBoxLayout *layout1 = new QVBoxLayout();
    for(int i = 0; i < number; i++){
        task[i].change_task_id(i);
        layout1->addWidget(&task[i]);
    }
    ui->task_list->setLayout(layout1);
}
void MainWindow::confirm_task(){
    task_num = ui->task_num->text().toInt();
    //"{\nrostopic pub /task_change task_server/taskchangeValue "action: 0 \ntask:\n  id: 0\n  position: {x: 5.0, y: 0.0, z: 0.0}\n  time: 10.0\n  profit: 7.0\n  complete: false"\n} ";
    QString s = "{";
    //s = s +'\n'+"rostopic pub /task_change task_server/taskchangeValue "+ '\"'+"action: 0 "+'\n'+"task:"+'\n'+"  id: 0"+'\n'+"  position: {x: 5.0, y: 0.0, z: 0.0}"+'\n'+"  time: 10.0"+'\n'+"  profit: 7.0"+'\n'+"  complete: false"+'\"'+'\n'+"}";
    s = s +'\n'+"rostopic pub /task_change task_server/taskchangeValue "+ '\"'+"action: 0 "+'\n'+"task:"+'\n'+"  id: %1 "+'\n'+"  position: {x: %2.0, y: %3.0, z: %4.0}"+'\n'+"  time: %5.0"+'\n'+"  profit: %6.0"+'\n'+"  complete: false"+'\"'+'\n'+"}";
    try {
        for(int i = 0;i < task_num; i++){
            QString s = "{";
            //s = s +'\n'+"rostopic pub /task_change task_server/taskchangeValue "+ '\"'+"action: 0 "+'\n'+"task:"+'\n'+"  id: 0"+'\n'+"  position: {x: 5.0, y: 0.0, z: 0.0}"+'\n'+"  time: 10.0"+'\n'+"  profit: 7.0"+'\n'+"  complete: false"+'\"'+'\n'+"}";
            s = s +'\n'+"rostopic pub /task_change task_server/taskchangeValue "+ '\"'+"action: 0 "+'\n'+"task:"+'\n'+"  id: %1 "+'\n'+"  position: {x: %2.0, y: %3.0, z: %4.0}"+'\n'+"  time: %5.0"+'\n'+"  profit: %6.0"+'\n'+"  complete: false"+'\"'+'\n'+"}";
            QString x = task[i].read_x();
            QString y = task[i].read_y();
            QString z = task[i].read_z();
            QString time = task[i].read_time();
            QString profit = task[i].read_profit();
            QString a = QString::number(i);
            s = s.arg(a).arg(x).arg(y).arg(z).arg(time).arg(profit);
            //qDebug() << s;
            cmd(s);

        }
    } catch (...) {
        qDebug() << "there is an error";
    }


}
/*****************************************************************************
** 实现机器人的添加和删除
*****************************************************************************/
void MainWindow::robot_gazebo(){
    //记录当前机器人数量
    wheel_num = ui->Wheel_Num->text().toInt();
    track_num = ui->Track_Num->text().toInt();
    drone_num = ui->Drone_Num->text().toInt();
    //添加环境模型
    if(g_a == 0)
    {
        ui->Num_Confirm->setDisabled(true);
    }
    //添加机器人
//    int wheel_num = ui->Wheel_Num->text().toInt();
    for (int i = 0; i < wheel_num; i++){
        QString robot = "roslaunch test_wheel wheel_robot.launch";
        QString amcl_robot = "roslaunch robot_navigation amcl_robot.launch";
        QString move_base = "roslaunch robot_navigation move_base_0.launch";
        QString pub_robot = "{";
        QString x = Wheel[i].Read_x();
        QString y = Wheel[i].Read_y();
        QString z = Wheel[i].Read_z();
        robot = robot+" ns:="+"robot"+QString::number(i)+" x:="+x+" y:="+y+" z:="+z;
        amcl_robot = amcl_robot+" ns:="+"robot"+QString::number(i)+" initial_pose_x:="+x+" initial_pose_y:="+y;
        move_base = move_base+" ns:="+"robot"+QString::number(i)+" num:="+QString::number(i);
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 0, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(QString::number(i));
        cmd(robot);
        cmd(amcl_robot);
        cmd(move_base);
        cmd(pub_robot);
        //设置已加入的机器人加入按钮无效
        Wheel[i].disable_add_robot();
    }
    for (int i = 10; i < track_num + 10; i++){
        QString robot = "roslaunch test_crawler crawler_robot.launch";
        QString amcl_robot = "roslaunch robot_navigation amcl_robot.launch";
        QString move_base = "roslaunch robot_navigation move_base_0.launch";
        QString pub_robot = "{";
        QString x = Track[i-10].Read_x();
        QString y = Track[i-10].Read_y();
        QString z = Track[i-10].Read_z();
        robot = robot+" ns:="+"robot"+QString::number(i)+" x:="+x+" y:="+y+" z:="+z;
        amcl_robot = amcl_robot+" ns:="+"robot"+QString::number(i)+" initial_pose_x:="+x+" initial_pose_y:="+y;
        move_base = move_base+" ns:="+"robot"+QString::number(i)+" num:="+QString::number(i);
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 1, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(QString::number(i));
        cmd(robot);
        cmd(amcl_robot);
        cmd(move_base);
        cmd(pub_robot);
        //设置已加入的机器人加入按钮无效
        Track[i-10].disable_add_robot();
    }
    for (int i = 20; i < drone_num + 20; i++){
        QString robot = "roslaunch rotors_gazebo drone.launch";
        QString pub_robot = "{";
        QString x = Drone[i - 20].Read_x();
        QString y = Drone[i - 20].Read_y();
        QString z = Drone[i - 20].Read_z();
        robot = robot+" ns:="+"robot"+QString::number(i)+" x:="+x+" y:="+y+" z:="+z;
        pub_robot = pub_robot +'\n'+"rostopic pub /robot_change robot_server/robotchangeValue \"action: 0"+'\n'+"robot_base: {id: %1, type: 2, energy_consumption: 0.0, max_1: 0.0, max_2: 0.0, state: true}\" " +'\n'+"}";
        pub_robot = pub_robot.arg(QString::number(i));
        cmd(robot);
        cmd(pub_robot);
        //设置已加入的机器人加入按钮无效
        Drone[i - 20].disable_add_robot();
    }

    ui->Num_Confirm->setDisabled(true);
    ui->Wheel_Num->setDisabled(true);
    ui->Track_Num->setDisabled(true);
    ui->Drone_Num->setDisabled(true);
    for(int i=0;i<wheel_num;i++){
        Wheel[i].disable_change_position();
    }
    for(int i=0;i<track_num;i++){
        Track[i].disable_change_position();
    }
    for(int i=0;i<drone_num;i++){
        Drone[i].disable_change_position();
    }
    ui->add_wheel->setEnabled(true);
    ui->add_crawler->setEnabled(true);
    ui->add_drone->setEnabled(true);
}

/*****************************************************************************
** 实现和rosmaster的连接
*****************************************************************************/

/*****************************************************************************
** 读写配置文件
*****************************************************************************/
void MainWindow::ReadSettings(){
    QSettings settings("RobotSim", "RobotSim");
    //设置文件编码，配置文件中使用中文时，这是必须的，否则乱码
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://127.0.0.1/")).toString();
    QString host_url = settings.value("host_url", QString("127.0.0.1")).toString();
    ui->edit_master->setText(master_url);
    ui->edit_host->setText(host_url);

    //读取快捷指令的setting
    QSettings Quick_Setting("RobotSim","Quick_Setting");
    QStringList ch_key=Quick_Setting.childKeys();
    for(auto c:ch_key)
    {
        add_quick_cmd(c,Quick_Setting.value(c,QString("")).toString());
    }

    //读取机器人位置信息
    QSettings Position("RobotSim","Position");
    ui->Wheel_Num->setText(Position.value("Wheel_Num").toString());
    this->Wheel_Init(Position.value("Wheel_Num").toString());
    ui->Track_Num->setText(Position.value("Track_Num").toString());
    this->Track_Init(Position.value("Track_Num").toString());
    ui->Drone_Num->setText(Position.value("Drone_Num").toString());
    this->Drone_Init(Position.value("Drone_Num").toString());
    for(int i = 0;i < Position.value("Wheel_Num").toInt();i++)
    {
        Wheel[i].Write_xyz(Position.value("Wheel_x"+QString::number(i,10)).toString(),Position.value("Wheel_y"+QString::number(i,10)).toString(),Position.value("Wheel_z"+QString::number(i,10)).toString());
    }
    for(int i = 0;i < Position.value("Track_Num").toInt();i++)
    {
        Track[i].Write_xyz(Position.value("Track_x"+QString::number(i,10)).toString(),Position.value("Track_y"+QString::number(i,10)).toString(),Position.value("Track_z"+QString::number(i,10)).toString());
    }
    for(int i = 0;i < Position.value("Drone_Num").toInt();i++)
    {
        Drone[i].Write_xyz(Position.value("Drone_x"+QString::number(i,10)).toString(),Position.value("Drone_y"+QString::number(i,10)).toString(),Position.value("Drone_z"+QString::number(i,10)).toString());
    }

    //读取任务相关信息
    QSettings task_info("RobotSim","task_info");
    ui->task_num->setText(task_info.value("task_num").toString());
    this->init_task(task_info.value("task_num").toString());
    for(int i = 0; i < task_info.value("task_num").toInt(); i++){
        QString x = task_info.value("task_x"+QString::number(i,10)).toString();
        QString y = task_info.value("task_y"+QString::number(i,10)).toString();
        QString z = task_info.value("task_z"+QString::number(i,10)).toString();
        QString time = task_info.value("task_time"+QString::number(i,10)).toString();
        QString profit = task_info.value("task_profit"+QString::number(i,10)).toString();
        task[i].write_message(x,y,z,time,profit);
    }

}

void MainWindow::WriteSettings(){
    //存下初始界面的参数
    QSettings settings("RobotSim", "RobotSim");
    settings.setValue("master_url",ui->edit_master->text());
    settings.setValue("host_url",ui->edit_host->text());
    //settings.setValue("topic_name",ui->line_edit_topic->text());
    //settings.setValue("use_environment_variables",QVariant(ui->checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    //settings.setValue("windowState", saveState());
    //settings.setValue("remember_settings",QVariant(ui->checkbox_remember_settings->isChecked()));

    //存下快捷指令的setting
    QSettings Quick_Setting("RobotSim","Quick_Setting");
    Quick_Setting.clear();
    for(int i = 0;i<ui->treeWidget_quick_cmd->topLevelItemCount();i++)
    {
        QTreeWidgetItem *top=ui->treeWidget_quick_cmd->topLevelItem(i);
        QTextEdit *cmd_val= static_cast<QTextEdit *>(ui->treeWidget_quick_cmd->itemWidget(top->child(0),1));
        Quick_Setting.setValue(top->text(0),cmd_val->toPlainText());
    }
    //存下机器人的数量和位置信息
    QSettings Position("RobotSim","Position");
    Position.clear();
    int a,b,c;
    a = ui->Wheel_Num->text().toInt();
    b = ui->Track_Num->text().toInt();
    c = ui->Drone_Num->text().toInt();
    Position.setValue("Wheel_Num",a);
    Position.setValue("Track_Num",b);
    Position.setValue("Drone_Num",c);
    for(int i = 0; i < a; i++)
    {
        Position.setValue("Wheel_x" + QString::number(i,10),Wheel[i].Read_x());
        Position.setValue("Wheel_y" + QString::number(i,10),Wheel[i].Read_y());
        Position.setValue("Wheel_z" + QString::number(i,10),Wheel[i].Read_z());
    }
    for(int i = 0; i < b; i++)
    {
        Position.setValue("Track_x" + QString::number(i,10),Track[i].Read_x());
        Position.setValue("Track_y" + QString::number(i,10),Track[i].Read_y());
        Position.setValue("Track_z" + QString::number(i,10),Track[i].Read_z());
    }
    for(int i = 0; i < c; i++)
    {
        Position.setValue("Drone_x" + QString::number(i,10),Drone[i].Read_x());
        Position.setValue("Drone_y" + QString::number(i,10),Drone[i].Read_y());
        Position.setValue("Drone_z" + QString::number(i,10),Drone[i].Read_z());
    }
    //存储任务相关内容
    QSettings task_info("RobotSim","task_info");
    task_info.clear();
    int d = ui->task_num->text().toInt();
    task_info.setValue("task_num",d);
    for(int i = 0; i < d ; i++){
        task_info.setValue("task_x"+QString::number(i,10),task[i].read_x());
        task_info.setValue("task_y"+QString::number(i,10),task[i].read_y());
        task_info.setValue("task_z"+QString::number(i,10),task[i].read_z());
        task_info.setValue("task_time"+QString::number(i,10),task[i].read_time());
        task_info.setValue("task_profit"+QString::number(i,10),task[i].read_profit());
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    WriteSettings();
    delete [] Wheel;
    delete [] Track;
    delete [] Drone;
//    newp1->kill();
    qDebug() << "gg" ;
    cmd("pkill rosmaster");
    cmd("pkill robot");
    cmd("pkill amcl");
    cmd("pkill move_base");
    cmd("pkill rostopic");
    //delete quick_cmd;
    QMainWindow::closeEvent(event);
}

/*****************************************************************************
** 实现快捷指令
*****************************************************************************/

//快捷指令删除按钮
void MainWindow::quick_cmd_remove()
{
    QTreeWidgetItem *curr=ui->treeWidget_quick_cmd->currentItem();
    //没有选择节点
    if(curr == nullptr) return;
    //获取父节点
    QTreeWidgetItem* parent=curr->parent();
    //如果当前节点就为父节点
    if(parent == nullptr)
    {
        ui->treeWidget_quick_cmd->takeTopLevelItem(ui->treeWidget_quick_cmd->indexOfTopLevelItem(curr));
        delete curr;
    }
    else{
        ui->treeWidget_quick_cmd->takeTopLevelItem(ui->treeWidget_quick_cmd->indexOfTopLevelItem(parent));
        delete parent;
    }


}
//快捷指令添加按钮
void MainWindow::quick_cmd_add()
{
    QWidget *w=new QWidget;
    //阻塞其他窗体
    w->setWindowModality(Qt::ApplicationModal);
    QLabel *name=new QLabel;
    name->setText("名称:");
    QLabel *content=new QLabel;
    content->setText("脚本:");
    QLineEdit *name_val=new QLineEdit;
    QTextEdit *shell_val=new QTextEdit;
    QPushButton *ok_btn=new QPushButton;
    ok_btn->setText("ok");
    ok_btn->setIcon(QIcon("://images/ok.png"));
    QPushButton *cancel_btn=new QPushButton;
    cancel_btn->setText("cancel");
    cancel_btn->setIcon(QIcon("://images/false.png"));
    QHBoxLayout *lay1=new QHBoxLayout;
    lay1->addWidget(name);
    lay1->addWidget(name_val);
    QHBoxLayout *lay2=new QHBoxLayout;
    lay2->addWidget(content);
    lay2->addWidget(shell_val);
    QHBoxLayout *lay3=new QHBoxLayout;
    lay3->addWidget(ok_btn);
    lay3->addWidget(cancel_btn);
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addLayout(lay1);
    v1->addLayout(lay2);
    v1->addLayout(lay3);

    w->setLayout(v1);
    w->show();

    connect(ok_btn,&QPushButton::clicked,[this,w,name_val,shell_val]
    {
        this->add_quick_cmd(name_val->text(),shell_val->toPlainText());
        w->close();
    });
}
//向treeWidget添加快捷指令
void MainWindow::add_quick_cmd(QString name,QString val)
{
    if(name=="") return;
    QTreeWidgetItem *head=new QTreeWidgetItem(QStringList()<<name);
    this->ui->treeWidget_quick_cmd->addTopLevelItem(head);
    QCheckBox *check=new QCheckBox;
    //记录父子关系
    this->widget_to_parentItem_map[check]=head;
    //连接checkbox选中的槽函数
    connect(check,SIGNAL(stateChanged(int)),this,SLOT(quick_cmds_check_change(int)));
    this->ui->treeWidget_quick_cmd->setItemWidget(head,1,check);
    QTreeWidgetItem *shell_content=new QTreeWidgetItem(QStringList()<<"shell");
    QTextEdit *shell_val=new QTextEdit;
    shell_val->setMaximumWidth(150);
    shell_val->setMaximumHeight(40);
    head->addChild(shell_content);
    shell_val->setText(val);
    this->ui->treeWidget_quick_cmd->setItemWidget(shell_content,1,shell_val);
}
//快捷指令按钮处理的函数
void MainWindow::quick_cmds_check_change(int state)
{

    QCheckBox* check = qobject_cast<QCheckBox*>(sender());
    QTreeWidgetItem *parent=widget_to_parentItem_map[check];
    QString bash = static_cast<QTextEdit *>(ui->treeWidget_quick_cmd->itemWidget(parent->child(0),1))->toPlainText();
    bool is_checked = state>1 ? true : false;
    if(is_checked)
    {
        cmd(bash);
    }
    else{

    }

}
//执行一些命令的回显
void MainWindow::cmd_output()
{

    ui->cmd_output->append(quick_cmd->readAllStandardOutput());
}
//执行一些命令的错误回显
void MainWindow::cmd_error_output()
{
    ui->cmd_output->append("<font color=\"#FF0000\">"+quick_cmd->readAllStandardError()+"</font> ");
}




void MainWindow::on_Rviz_clicked()
{
    QString rviz = "roslaunch robot_navigation navigation.launch";
    cmd(rviz);
}

void MainWindow::on_world_clicked()
{
    QString world = "roslaunch test_wheel only_world.launch";
    cmd(world);
}



void MainWindow::on_module_1_clicked()
{
    QString module_1= "rosrun split_area split_example.py";
    cmd(module_1);
}

void MainWindow::on_modele_2_clicked()
{
    QString module_2= "rosrun allocation_within_area result_publisher.py";
    cmd(module_2);
}

void MainWindow::on_module_3_clicked()
{
    QProcess::startDetached("/home/shan/catkin_wq/src/bash/module_3.sh");
}

void MainWindow::on_module_4_clicked()
{
    QString module_4_1 = "{";
    QString module_4_2 =  "rosservice call /gazebo/apply_body_wrench \"body_name: 'unit_box::link'";
    QString module_4_3 = "reference_frame: 'world'";
    QString module_4_4 = "reference_point: {x: 0.0, y: 0.0, z: 0.0}";
    QString module_4_5 = "wrench:";
    QString module_4_6 = "  force: {x: 5.0, y: 0.0, z: 0.0}";
    QString module_4_7 = "  torque: {x: 0.0, y: 0.0, z: 0.0}";
    QString module_4_8 = "start_time: {secs: 0, nsecs: 0}";
    QString module_4_9 = "duration: {secs: 3, nsecs: 0}\"";
    QString module_4_10 = "}";
    QString total;
    total = module_4_1 + '\n' + module_4_2 + '\n' + module_4_3 + '\n' + module_4_4 + '\n' + module_4_5 +'\n' + module_4_6 + '\n' + module_4_7 + '\n' + module_4_8 + '\n' + module_4_9 + '\n' + module_4_10;
    cmd(total);
}

void MainWindow::on_robot_server_clicked()
{
    QProcess::startDetached("/home/shan/catkin_wq/src/bash/robot_server.sh");

//    newp1->start("bash");
////    QString bash = "rosrun robot_server robot_server_node.py";
//        QString bash = "roscore";
//    qDebug() << bash.toLocal8Bit()+'\n';
//    newp1->write(bash.toLocal8Bit()+'\n');
}

void MainWindow::on_task_server_clicked()
{
    QProcess::startDetached("/home/shan/catkin_wq/src/bash/task_server.sh");
}

void MainWindow::on_task_exe_clicked()
{
    QProcess::startDetached("/home/shan/catkin_wq/src/bash/task_exe.sh");
}

void MainWindow::on_draw_area_clicked()
{
    QProcess::startDetached("/home/shan/catkin_wq/src/bash/split_area.sh");
}
