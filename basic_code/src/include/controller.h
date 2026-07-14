#include <Eigen/Geometry>
#include <iostream>

#ifndef CONTROLLER_H
#define CONTROLLER_H



void controller_init(double input_p_gain, Eigen::Vector3d input_PID_gains, double input_sampling_time);
Eigen::Vector3d control_system_output(Eigen::Vector3d current_angle_states);



#endif