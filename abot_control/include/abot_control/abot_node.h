/**
 *@title ROS for Abot
 * Copyright: Copyright (c) 2019 Abot [https://github.com/tloinny/ROS-for-Abot]
 *
 *@date on 2019-3-11
 *@author:tony-lin
 *@version 1.0.0
 *
 *@description: ROS node class
 */

#ifndef ABOT_NODE_H
#define ABOT_NODE_H

#include "abot_control/abot_control.h"
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <math.h>

typedef actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> AbotServer;

namespace abot {
  class abot_node
  {
    public:
      abot_node(int argc, char** argv);
      void Send2Serial(const control_msgs::FollowJointTrajectoryGoalConstPtr& a_goal, AbotServer* as/*, abot::Abot_control* robot*/);
    private:
      ros::Publisher JointStatePublisher;
      //AbotServer abotServer;
      Abot_control* Abot_controller;
      int init_argc;
      char** init_argv;
  };
}

#endif // ABOT_NODE_H
