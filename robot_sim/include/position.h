#ifndef POSITION_H
#define POSITION_H

#include <QWidget>
#include <QProcess>
namespace Ui {
class position;
}

class position : public QWidget
{
    Q_OBJECT

public:
    explicit position(QWidget *parent = nullptr);
    ~position();
    void changeLabel(QString s,int a);
    void ReadPosition();
    QString Read_x();
    QString Read_y();
    QString Read_z();
    void Write_xyz(QString x,QString y,QString z);
    void disable_add_robot();
    void disable_change_position();
    void cmd(QString bash);
    friend class mainwindow;
    Ui::position *ui;
    QProcess *quick_cmd = nullptr;
//    void send_delete_robot()
//    {
//        emit delete_robot1();
//    }
//signals:
//    void delete_robot1();


//public slots:
//    //添加和删除机器人
////    void add_robot();
//    void delete_robot();

private slots:
    void on_delete_robot_clicked();

private slots:
    void on_add_robot_clicked();

private:
};

#endif // POSITION_H
