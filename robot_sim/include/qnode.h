/**
 * @file /include/ros_qt/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ros_qt_QNODE_HPP_
#define ros_qt_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include "allocation_within_area/one_sequence.h"
#include "allocation_within_area/allocationResult.h"
#include "split_area/drawResult.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/



/*****************************************************************************
** Class
*****************************************************************************/
typedef struct point {
    float x;
    float y;
} my_point;

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv );
    virtual ~QNode();
    bool init(const std::string &master_url, const std::string &host_url);
    void run();
    bool is_point_in_rect(my_point A, my_point B, point C, point D,float x, float y);

    /*********************
    ** Logging
    **********************/
    enum LogLevel {
             Debug,
             Info,
             Warn,
             Error,
             Fatal
     };

    QStringListModel* loggingModel2() { return &logging_model2; }
    QStringListModel* loggingModel1() { return &logging_model1; }
    void log1( const LogLevel &level, const std::string &msg);
    void log2( const LogLevel &level, const std::string &msg);


Q_SIGNALS:
    void loggingUpdated1();
    void loggingUpdated2();
    void rosShutdown();

private:
    bool init();
    int init_argc;
    char** init_argv;
    ros::Subscriber task_2;
    ros::Subscriber task_1;
    ros::ServiceClient client;
    //ros::NodeHandle n;
    QStringListModel logging_model1;
    QStringListModel logging_model2;
    void task_2_call_back(const allocation_within_area::allocationResult::ConstPtr &msg);
    void task_1_call_back(const split_area::drawResult &msg);

};


#endif /* ros_qt_QNODE_HPP_ */
