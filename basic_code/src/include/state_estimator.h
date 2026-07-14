#include <Eigen/Geometry>

#ifndef STATE_ESTIMATOR_H
#define STATE_ESTIMATOR_H

using Quaterniond = Eigen::Quaternion<double>;


Eigen::Vector3d state_estimator(Quaterniond measured_q);



#endif