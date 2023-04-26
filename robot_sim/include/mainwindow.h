#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTreeWidgetItem>
#include "position.h"
#include "task_list.h"
#include "qnode.h"
#include <QProcess>
#include <vector>
#include <memory>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, shared_ptr<QProcess>& p1, QWidget *parent = nullptr);
    ~MainWindow();
    position *Wheel=new position[10];
    position *Track=new position[10];
    position *Drone=new position[5];
    task_list *task = new task_list[20];
    int wheel_num=0;
    int track_num=0;
    int drone_num=0;
    int task_num=0;
    int addition_wheel_num=0;
    int addition_track_num=0;
    int addition_drone_num=0;

    void cmd(QString bash);
    void showNoMasterMessage();
    void showRobotMessage();

    void ReadSettings(); // 读配置
    void WriteSettings(); // 写配置
    vector<vector<QString>> remember_position(int a);
    vector<vector<QString>> remember_task();
    void load_position(int a, vector<vector<QString>> r_p);
    void load_task(vector<vector<QString>> r_p);

    // 重载函数 用来在关闭界面前写入配置
    void closeEvent(QCloseEvent *event); 

//    //自定义信号用于初始化
//    void send(QString s)
//       {
//           emit RobotInit(s);     //通过emit关键字发射信号
//       }
//   signals:                    //使用signals声明信号函数，访问级别为protected
//    void RobotInit(QString s);     //信号只能声明不能定义
    
    public slots:
    void slot_tab_manage_currentChanged(int index);
    
    void InitUi();
    void Wheel_Init(QString s);
    void Track_Init(QString s);
    void Drone_Init(QString s);
    //添加额外的机器人
    void add_addition_wheel();
    void add_addition_track();
    void add_addition_drone();

    void quick_cmd_add();
    void quick_cmd_remove();
    void quick_cmds_check_change(int);
    void cmd_output();
    void cmd_error_output();

    void robot_gazebo();
    //void delete_robot(int i);
    void init_task(QString s);
    void confirm_task();
    void button_connect_clicked();
    void updateLoggingView2();
    void updateLoggingView1();
private slots:
    void on_draw_area_clicked();

private slots:
    void on_task_exe_clicked();

private slots:
    void on_task_server_clicked();

private slots:
    void on_robot_server_clicked();

private slots:
    void on_module_4_clicked();

private slots:
    void on_module_3_clicked();

private slots:
    void on_modele_2_clicked();

private slots:
    void on_module_1_clicked();


private slots:
    void on_world_clicked();

private slots:
    void on_Rviz_clicked();

private:
    Ui::MainWindow *ui;
    void add_quick_cmd(QString name,QString shell);
    //记录父子关系
    QMap <QWidget*,QTreeWidgetItem *> widget_to_parentItem_map;
    std::shared_ptr<QProcess> newp1;
    QProcess *quick_cmd = nullptr;
    QNode qnode;
    //QProcess *close_remote_cmd = nullptr;
    //QProcess *base_cmd = nullptr;
};
#endif // MAINWINDOW_H
