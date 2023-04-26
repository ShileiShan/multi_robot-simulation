/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "qnode.h"
#include "allocation_within_area/allocationResult.h"
#include "allocation_within_area/one_sequence.h"
#include "gazebo_msgs/GetModelState.h"
#include "qdebug.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/



/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)
    {}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
    wait();
}

//bool QNode::init() {
//    ros::init(init_argc,init_argv,"ros_qt");
//    if ( ! ros::master::check() ) {
//        return false;
//    }
//    ros::start(); // explicitly needed since our nodehandle is going out of scope.
//    ros::NodeHandle n;
//    // Add your ros communications here.
//    chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
//    start();
//    return true;
//}

bool QNode::init() {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = "http://127.0.0.1:11311/";
    remappings["__hostname"] = "127.0.0.1";
    ros::init(remappings,"ros_qt");
    ros::start();
    start();
    return true;
}

void QNode::task_1_call_back(const split_area::drawResult &msg){
    my_point A;
    my_point B;
    my_point C;
    my_point D;
    A.x = msg.area[0].x;
    A.y = msg.area[0].y;
    B.x = msg.area[1].x;
    B.y = msg.area[1].y;
    C.x = msg.area[2].x;
    C.y = msg.area[2].y;
    D.x = msg.area[3].x;
    D.y = msg.area[3].y;
    ros::NodeHandle n2;
    client = n2.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
    gazebo_msgs::GetModelState srv2;
    if(msg.color == -1){

    }
    else{
        QString area = "区域";
        area = area + QString::number(msg.color) + ":";
        QString robot;
        QString total;
        for(int i = 0; i < 20; i++){
            srv2.request.model_name = "robot" + std::to_string(i);
            if (client.call(srv2))
            {
        //        qDebug()<<"robot0 in this area";
                float x = srv2.response.pose.position.x;
                float y = srv2.response.pose.position.y;
                if(is_point_in_rect(A, B, C, D, x, y)){
                    robot = robot + "robot" + QString::number(i) + ",";
                    //qDebug()<<"robot0 in this area";
                }
            }
            else
            {
                ROS_ERROR("Failed to call service /gazebo/get_model_state");
            }
        }
        total = area + robot;
        log1(Info, total.toStdString());
    }
}
bool QNode::is_point_in_rect(my_point A, my_point B, my_point C, my_point D,float x, float y) {
    int a = (B.x - A.x)*(y - A.y) - (B.y - A.y)*(x - A.x);
    int b = (C.x - B.x)*(y - B.y) - (C.y - B.y)*(x - B.x);
    int c = (D.x - C.x)*(y - C.y) - (D.y - C.y)*(x - C.x);
    int d = (A.x - D.x)*(y - D.y) - (A.y - D.y)*(x - D.x);
    if((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0)) {
        return true;
    }

//      AB X AP = (b.x - a.x, b.y - a.y) x (p.x - a.x, p.y - a.y) = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
//      BC X BP = (c.x - b.x, c.y - b.y) x (p.x - b.x, p.y - b.y) = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
    return false;
}

void QNode::task_2_call_back(const allocation_within_area::allocationResult::ConstPtr &msg){
    //allocation_within_area::one_sequence a;
//    qDebug() << "hello,world";
    logging_model2.removeRows(0,logging_model2.rowCount());
    for(auto a:msg->robot_sequences){
        QString id = "机器人";
        id = id + QString::number(a.id,10);
        QString task_list = "任务顺序:";
        for(auto i:a.targets){
            task_list += QString::number(i,10) + ' ';
        }
        QString total = id + task_list;
        //task_2_list<<total;
        log2(Info,total.toStdString());
    }
}
bool QNode::init(const std::string &master_url, const std::string &host_url) {
    std::map<std::string,std::string> remappings;
    remappings["__master"] = master_url;
    remappings["__hostname"] = host_url;
    ros::init(remappings,"ros_qt");
    if ( ! ros::master::check() ) {
        return false;
    }
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
     //Add your ros communications here.
    ros::NodeHandle n;
    task_2 = n.subscribe<allocation_within_area::allocationResult>("/allocation_result",1,&QNode::task_2_call_back,this);
    task_1 = n.subscribe("/area_result",1,&QNode::task_1_call_back,this);
    //task_2 = n.subscribe("/allocation_result",1,&QNode::task_2_call_back,this);
    //chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
    //启动多线程函数 run()
    //ros::spin();
    start();
    return true;
}

void QNode::run() {
    ros::Rate loop_rate(1);
//    int count = 0;
    while ( ros::ok() ) {
        ros::spinOnce();
        loop_rate.sleep();
//        qDebug() << "have a look";
//        ++count;
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log1( const LogLevel &level, const std::string &msg) {
    logging_model1.insertRows(logging_model1.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model1.setData(logging_model1.index(logging_model1.rowCount()-1),new_row);
    Q_EMIT loggingUpdated1(); // used to readjust the scrollbar
}
void QNode::log2( const LogLevel &level, const std::string &msg) {
    logging_model2.insertRows(logging_model2.rowCount(),1);
    std::stringstream logging_model_msg;
    switch ( level ) {
        case(Debug) : {
                ROS_DEBUG_STREAM(msg);
                logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Info) : {
                ROS_INFO_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Warn) : {
                ROS_WARN_STREAM(msg);
                logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Error) : {
                ROS_ERROR_STREAM(msg);
                logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
                break;
        }
        case(Fatal) : {
                ROS_FATAL_STREAM(msg);
                logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
                break;
        }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model2.setData(logging_model2.index(logging_model2.rowCount()-1),new_row);
    Q_EMIT loggingUpdated2(); // used to readjust the scrollbar
}


