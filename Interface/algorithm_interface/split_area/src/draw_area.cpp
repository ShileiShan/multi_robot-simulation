#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
 
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <split_area/drawResult.h>

#include <cmath>
 
using namespace std;


class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    marker_pub_ = n_.advertise<visualization_msgs::Marker>("/visualization_marker", 1);
 
    //Topic you want to subscribe
    area_info_sub_ = n_.subscribe("/area_result", 1, &SubscribeAndPublish::drawareaCallback, this);
  }
  //设定回调函数
  void drawareaCallback(const split_area::drawResult::ConstPtr& msg)
  {
	//建立对象Marker 用于框选机器人
	visualization_msgs::Marker line_strip;
	line_strip.header.frame_id = "/map";
	line_strip.header.stamp = ros::Time::now();      
	line_strip.action = visualization_msgs::Marker::ADD;

	line_strip.id = msg->color;
	line_strip.type = visualization_msgs::Marker::LINE_STRIP;
	line_strip.pose.orientation.w = 1.0;
	//命名
	line_strip.ns = "area_result";
	line_strip.scale.x = 0.3;
	line_strip.lifetime = ros::Duration();
	//choose color
	switch(msg->color)
	{
		case 1: line_strip.color.b = 0.0; line_strip.color.g = 1.0; line_strip.color.r = 0.0; line_strip.color.a = 1.0; break;
		case 2: line_strip.color.b = 1.0; line_strip.color.g = 0.0; line_strip.color.r = 0.0; line_strip.color.a = 1.0; break;
		case 3: line_strip.color.b = 0.0; line_strip.color.g = 0.0; line_strip.color.r = 1.0; line_strip.color.a = 1.0; break;
		case 4: line_strip.color.b = 0.0; line_strip.color.g = 1.0; line_strip.color.r = 1.0; line_strip.color.a = 1.0; break;
		case -1: line_strip.action = visualization_msgs::Marker::DELETEALL; marker_pub_.publish(line_strip); break;
		default: ROS_ERROR("No define area number"); return;
	}

	ROS_INFO("%d",msg->color);
	//将从msg中获取的信息传给point p
	geometry_msgs::Point p;
	p.x = msg->area[0].x;
	p.y = msg->area[0].y;
	p.z = msg->area[0].z;
	line_strip.points.push_back(p);

	p.x = msg->area[1].x;
	p.y = msg->area[1].y;
	p.z = msg->area[1].z;
	line_strip.points.push_back(p);

	p.x = msg->area[2].x;
	p.y = msg->area[2].y;
	p.z = msg->area[2].z;
	line_strip.points.push_back(p);

	p.x = msg->area[3].x;
	p.y = msg->area[3].y;
	p.z = msg->area[3].z;
	line_strip.points.push_back(p);

	p.x = msg->area[0].x;
	p.y = msg->area[0].y;
	p.z = msg->area[0].z;
	line_strip.points.push_back(p);

	//while(1)
	marker_pub_.publish(line_strip);  
  }
 
private:
  ros::NodeHandle n_; 
  ros::Publisher marker_pub_;
  ros::Subscriber area_info_sub_;
 
};

/*void drawareaCallback(const split_area::drawResult::ConstPtr& msg)
{
	ros::NodeHandle n;
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("/visualization_marker", 10);
	visualization_msgs::Marker line_strip;
	line_strip.header.frame_id = "/map";
	line_strip.header.stamp = ros::Time::now();      
	line_strip.action = visualization_msgs::Marker::ADD;

	line_strip.id = 1;
	line_strip.type = visualization_msgs::Marker::LINE_STRIP;
	line_strip.pose.orientation.w = 1.0;

	line_strip.ns = "area_result";
	line_strip.scale.x = 0.3;
	line_strip.lifetime = ros::Duration();

	switch(msg->color)
	{
		case 1: line_strip.color.b = 0.0; line_strip.color.g = 1.0; line_strip.color.r = 0.0; line_strip.color.a = 1.0; break;
		case 2: line_strip.color.b = 1.0; line_strip.color.g = 0.0; line_strip.color.r = 0.0; line_strip.color.a = 1.0; break;
		case 3: line_strip.color.b = 0.0; line_strip.color.g = 0.0; line_strip.color.r = 1.0; line_strip.color.a = 1.0; break;
		case 4: line_strip.color.b = 0.0; line_strip.color.g = 1.0; line_strip.color.r = 1.0; line_strip.color.a = 1.0; break;
		default: ROS_ERROR("No define area number"); return;
	}

	ROS_INFO("%d",msg->color);

	geometry_msgs::Point p;
	p.x = msg->area[0].x;
	p.y = msg->area[0].y;
	p.z = msg->area[0].z;
	line_strip.points.push_back(p);

	p.x = msg->area[1].x;
	p.y = msg->area[1].y;
	p.z = msg->area[1].z;
	line_strip.points.push_back(p);

	p.x = msg->area[2].x;
	p.y = msg->area[2].y;
	p.z = msg->area[2].z;
	line_strip.points.push_back(p);

	p.x = msg->area[3].x;
	p.y = msg->area[3].y;
	p.z = msg->area[3].z;
	line_strip.points.push_back(p);

	p.x = msg->area[0].x;
	p.y = msg->area[0].y;
	p.z = msg->area[0].z;
	line_strip.points.push_back(p);

	//while(1)
	marker_pub.publish(line_strip);   
}*/
 
int main(int argc, char** argv)
{
	/* Define Marker Line */	
	ros::init(argc, argv, "spilt_area");
	//ros::NodeHandle n;
	//ros::Subscriber area_info_sub = n.subscribe("/area_result", 1, drawareaCallback);
	SubscribeAndPublish SAPObject;
	ROS_INFO("draw_area node run successfully");
	ros::spin();
	/*ros::Rate r(1);
 
    
	while (ros::ok())
	{
		ros::spinOnce();
		r.sleep();
	}*/
 
	return 0;
}

