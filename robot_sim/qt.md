## 非法输入检查功能：

QlineEdit控件作为输入框，可以从中读取到QString类型。

我们需要对读取出来的内容进行检查，读取的内容首先进行类型转换（转换函数为toInt()），对转换后的数字进行检查。

如果输入的不是0-10以内的内容，则通过throw关键字抛出异常，并由catch捕获异常并将异常输出。

## 智能指针使用：

智能指针指向系统终端命令，当指针销毁时，将该部分内存自动释放。

## 多线程程序编写：

为了将Ros和Qt集成，使用Qt的界面显示Ros的消息，因此需要一边保持运行界面，一边运行Qnode节点监听话题的消息，因此使用多线程来完成这个任务。

Qt中的Qnode 

## ROS节点编写流程：

ROS节点句柄 发送者 订阅者

自定义消息，先写然后修改Cmakelist文件最后导入消息

使用其他功能包的消息，现将功能包中文件添加到CMakeLists中

小技巧：

查看当前ROS环境中的工作空间;

```sh
rospack profile
echo $ROS_PACKAGE_PATH
```

两个工作空间同时存在的办法：

假设有两个工作空间/home/user1/work1_ws ， /home/user1/work2_ws，怎么做呢？显示步骤是：

1）在work1_ws中执行catkin_make, 编译完成后，执行：source /home/user1/work1_ws/devel/setup.bash

2）在work2_ws中执行catkin_make, 编译完成后，执行：source /home/user1/work2_ws/devel/setup.bash



 

