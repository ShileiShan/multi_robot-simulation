/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *Tab_1;
    QWidget *Home;
    QLabel *xiaohui;
    QWidget *Task_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *MutiRobotGroup;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QListWidget *SingleRobotInfo;
    QWidget *Robot;
    QVBoxLayout *verticalLayout_13;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_10;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_11;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *label_12;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_4;
    QWidget *Rviz_2;
    QTabWidget *Tab_2;
    QWidget *Base;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_2;
    QWidget *Task;
    QVBoxLayout *verticalLayout_8;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_6;
    QRadioButton *radioButton_2;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButton_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;
    QWidget *Robot_2;
    QVBoxLayout *verticalLayout_15;
    QWidget *widget_13;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_12;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_3;
    QLineEdit *Wheel_Num;
    QLabel *label_8;
    QLineEdit *Track_Num;
    QLabel *label_9;
    QLineEdit *Drone_Num;
    QPushButton *Num_Confirm;
    QSpacerItem *verticalSpacer_3;
    QWidget *Rviz;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1300, 766);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Tab_1 = new QTabWidget(widget);
        Tab_1->setObjectName(QStringLiteral("Tab_1"));
        Home = new QWidget();
        Home->setObjectName(QStringLiteral("Home"));
        xiaohui = new QLabel(Home);
        xiaohui->setObjectName(QStringLiteral("xiaohui"));
        xiaohui->setGeometry(QRect(280, 170, 301, 281));
        xiaohui->setPixmap(QPixmap(QString::fromUtf8(":/Image/xiaohui.jpg")));
        Tab_1->addTab(Home, QString());
        Task_2 = new QWidget();
        Task_2->setObjectName(QStringLiteral("Task_2"));
        verticalLayout_4 = new QVBoxLayout(Task_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_2 = new QWidget(Task_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        MutiRobotGroup = new QTextEdit(widget_2);
        MutiRobotGroup->setObjectName(QStringLiteral("MutiRobotGroup"));

        verticalLayout_2->addWidget(MutiRobotGroup);


        verticalLayout_4->addWidget(widget_2);

        widget_3 = new QWidget(Task_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        SingleRobotInfo = new QListWidget(widget_3);
        SingleRobotInfo->setObjectName(QStringLiteral("SingleRobotInfo"));

        verticalLayout_3->addWidget(SingleRobotInfo);


        verticalLayout_4->addWidget(widget_3);

        Tab_1->addTab(Task_2, QString());
        Robot = new QWidget();
        Robot->setObjectName(QStringLiteral("Robot"));
        verticalLayout_13 = new QVBoxLayout(Robot);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        widget_12 = new QWidget(Robot);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        verticalLayout_14 = new QVBoxLayout(widget_12);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_10 = new QLabel(widget_12);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_14->addWidget(label_10);

        scrollArea = new QScrollArea(widget_12);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 846, 219));
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_14->addWidget(scrollArea);

        label_11 = new QLabel(widget_12);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_14->addWidget(label_11);

        scrollArea_2 = new QScrollArea(widget_12);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 846, 219));
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_14->addWidget(scrollArea_2);

        label_12 = new QLabel(widget_12);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_14->addWidget(label_12);

        scrollArea_3 = new QScrollArea(widget_12);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setMaximumSize(QSize(9999999, 100));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QStringLiteral("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 846, 98));
        scrollArea_3->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_14->addWidget(scrollArea_3);


        verticalLayout_13->addWidget(widget_12);

        Tab_1->addTab(Robot, QString());
        Rviz_2 = new QWidget();
        Rviz_2->setObjectName(QStringLiteral("Rviz_2"));
        Tab_1->addTab(Rviz_2, QString());

        horizontalLayout->addWidget(Tab_1);

        Tab_2 = new QTabWidget(widget);
        Tab_2->setObjectName(QStringLiteral("Tab_2"));
        Tab_2->setMinimumSize(QSize(370, 0));
        Tab_2->setMaximumSize(QSize(370, 16777215));
        Base = new QWidget();
        Base->setObjectName(QStringLiteral("Base"));
        verticalLayout_10 = new QVBoxLayout(Base);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        widget_10 = new QWidget(Base);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        verticalLayout_9 = new QVBoxLayout(widget_10);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_4 = new QLabel(widget_10);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_9->addWidget(label_4);

        lineEdit = new QLineEdit(widget_10);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_9->addWidget(lineEdit);

        label_5 = new QLabel(widget_10);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_9->addWidget(label_5);

        lineEdit_2 = new QLineEdit(widget_10);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout_9->addWidget(lineEdit_2);


        verticalLayout_10->addWidget(widget_10);

        widget_8 = new QWidget(Base);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        horizontalLayout_2 = new QHBoxLayout(widget_8);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_3 = new QPushButton(widget_8);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_2 = new QPushButton(widget_8);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_10->addWidget(widget_8);

        widget_9 = new QWidget(Base);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        horizontalLayout_4 = new QHBoxLayout(widget_9);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(widget_9);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        label_7 = new QLabel(widget_9);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setAutoFillBackground(true);
        label_7->setFrameShape(QFrame::Box);
        label_7->setFrameShadow(QFrame::Plain);

        horizontalLayout_4->addWidget(label_7);


        verticalLayout_10->addWidget(widget_9);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_2);

        Tab_2->addTab(Base, QString());
        Task = new QWidget();
        Task->setObjectName(QStringLiteral("Task"));
        verticalLayout_8 = new QVBoxLayout(Task);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        widget_7 = new QWidget(Task);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        verticalLayout_7 = new QVBoxLayout(widget_7);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        widget_4 = new QWidget(widget_7);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButton = new QRadioButton(widget_4);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout_3->addWidget(radioButton);


        verticalLayout_7->addWidget(widget_4);

        widget_5 = new QWidget(widget_7);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        verticalLayout_6 = new QVBoxLayout(widget_5);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        radioButton_2 = new QRadioButton(widget_5);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout_6->addWidget(radioButton_2);


        verticalLayout_7->addWidget(widget_5);

        widget_6 = new QWidget(widget_7);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        verticalLayout_5 = new QVBoxLayout(widget_6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        radioButton_3 = new QRadioButton(widget_6);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout_5->addWidget(radioButton_3);


        verticalLayout_7->addWidget(widget_6);

        pushButton = new QPushButton(widget_7);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_7->addWidget(pushButton);


        verticalLayout_8->addWidget(widget_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);

        Tab_2->addTab(Task, QString());
        Robot_2 = new QWidget();
        Robot_2->setObjectName(QStringLiteral("Robot_2"));
        verticalLayout_15 = new QVBoxLayout(Robot_2);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        widget_13 = new QWidget(Robot_2);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        verticalLayout_16 = new QVBoxLayout(widget_13);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        groupBox = new QGroupBox(widget_13);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_12 = new QVBoxLayout(groupBox);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        widget_11 = new QWidget(groupBox);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        verticalLayout_11 = new QVBoxLayout(widget_11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_3 = new QLabel(widget_11);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_11->addWidget(label_3);

        Wheel_Num = new QLineEdit(widget_11);
        Wheel_Num->setObjectName(QStringLiteral("Wheel_Num"));
        Wheel_Num->setReadOnly(false);

        verticalLayout_11->addWidget(Wheel_Num);

        label_8 = new QLabel(widget_11);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_11->addWidget(label_8);

        Track_Num = new QLineEdit(widget_11);
        Track_Num->setObjectName(QStringLiteral("Track_Num"));

        verticalLayout_11->addWidget(Track_Num);

        label_9 = new QLabel(widget_11);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_11->addWidget(label_9);

        Drone_Num = new QLineEdit(widget_11);
        Drone_Num->setObjectName(QStringLiteral("Drone_Num"));

        verticalLayout_11->addWidget(Drone_Num);


        verticalLayout_12->addWidget(widget_11);


        verticalLayout_16->addWidget(groupBox);

        Num_Confirm = new QPushButton(widget_13);
        Num_Confirm->setObjectName(QStringLiteral("Num_Confirm"));

        verticalLayout_16->addWidget(Num_Confirm);


        verticalLayout_15->addWidget(widget_13);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_15->addItem(verticalSpacer_3);

        Tab_2->addTab(Robot_2, QString());
        Rviz = new QWidget();
        Rviz->setObjectName(QStringLiteral("Rviz"));
        Tab_2->addTab(Rviz, QString());

        horizontalLayout->addWidget(Tab_2);


        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        Tab_1->setCurrentIndex(3);
        Tab_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        xiaohui->setText(QString());
        Tab_1->setTabText(Tab_1->indexOf(Home), QApplication::translate("MainWindow", "Home", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\345\244\232\346\234\272\345\231\250\344\272\272\344\273\273\345\212\241\345\210\206\347\273\204\344\277\241\346\201\257:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\215\225\346\234\272\345\231\250\344\272\272\344\273\273\345\212\241\345\210\206\351\205\215\344\277\241\346\201\257:", Q_NULLPTR));
        Tab_1->setTabText(Tab_1->indexOf(Task_2), QApplication::translate("MainWindow", "Task", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\350\275\256\345\274\217\346\234\272\345\231\250\344\272\272\344\275\215\347\275\256:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\345\261\245\345\270\246\345\274\217\346\234\272\345\231\250\344\272\272\344\275\215\347\275\256:", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "\346\227\240\344\272\272\346\234\272\344\275\215\347\275\256:", Q_NULLPTR));
        Tab_1->setTabText(Tab_1->indexOf(Robot), QApplication::translate("MainWindow", "Robot", Q_NULLPTR));
        Tab_1->setTabText(Tab_1->indexOf(Rviz_2), QApplication::translate("MainWindow", "Rviz", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\344\270\273\350\212\202\347\202\271\345\234\260\345\235\200:", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("MainWindow", "http://192.168.0.110:11311/", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\346\234\254\346\234\272IP:", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("MainWindow", "192.168.0.110", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "        \350\277\236\346\216\245\347\212\266\346\200\201:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200", Q_NULLPTR));
        Tab_2->setTabText(Tab_2->indexOf(Base), QApplication::translate("MainWindow", "Base", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\270\200", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\272\214", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("MainWindow", "\344\273\273\345\212\241\344\270\211", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        Tab_2->setTabText(Tab_2->indexOf(Task), QApplication::translate("MainWindow", "Task", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\234\272\345\231\250\344\272\272\346\225\260\351\207\217:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\350\275\256\345\274\217\346\234\272\345\231\250\344\272\272", Q_NULLPTR));
        Wheel_Num->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\345\261\245\345\270\246\345\274\217\346\234\272\345\231\250\344\272\272", Q_NULLPTR));
        Track_Num->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\346\227\240\344\272\272\346\234\272", Q_NULLPTR));
        Drone_Num->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        Num_Confirm->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", Q_NULLPTR));
        Tab_2->setTabText(Tab_2->indexOf(Robot_2), QApplication::translate("MainWindow", "Robot", Q_NULLPTR));
        Tab_2->setTabText(Tab_2->indexOf(Rviz), QApplication::translate("MainWindow", "Rviz", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
