#ifndef TASK_LIST_H
#define TASK_LIST_H

#include <QWidget>

namespace Ui {
class task_list;
}

class task_list : public QWidget
{
    Q_OBJECT

public:
    explicit task_list(QWidget *parent = nullptr);
    ~task_list();
    void change_task_id(int i);
    QString read_x();
    QString read_y();
    QString read_z();
    QString read_time();
    QString read_profit();
    void write_message(QString x, QString y, QString z, QString time, QString profit);
private:
    Ui::task_list *ui;
};

#endif // TASK_LIST_H
