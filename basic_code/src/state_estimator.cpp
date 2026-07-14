#include "include/state_estimator.h"

Eigen::Vector3d twist_axis_vector(1, 0, 0); // x axis rotations to remove

Quaterniond q_ref = Quaterniond(0.70710678, 0, 0.70710678, 0); //reference from 6dof frame, prob need to swap for us


Quaterniond attitude_error(Quaterniond measured_q) {
    Quaterniond q_error;
    Quaterniond conj_measured_q = measured_q.conjugate();

    q_error = q_ref * conj_measured_q;

    return q_error;
}

Quaterniond swing_twist_decompisition(Quaterniond q_error) {
    Quaterniond swing_q;
    Eigen::Vector3d v(q_error.x(), q_error.y(), q_error.z()); //placeholder vector
    double division_value = sqrt(pow(q_error.w(), 2)+pow(twist_axis_vector.dot(v), 2));

    Quaterniond twist_q((q_error.w())/division_value, (twist_axis_vector*(twist_axis_vector.dot(v)))/division_value);
    Quaterniond inverse_twist_q = twist_q.inverse();

    swing_q = inverse_twist_q * q_error;

    return swing_q;
}

Eigen::Vector3d axis_angle_error(Quaterniond swing_q) {
    Eigen::Vector3d v_error;

    v_error.x() = (2*acos(swing_q.w())) * (swing_q.x())/(sqrt(1 - (swing_q.w()*swing_q.w())));
    v_error.y() = (2*acos(swing_q.w())) * (swing_q.y())/(sqrt(1 - (swing_q.w()*swing_q.w())));
    v_error.z() = (2*acos(swing_q.w())) * (swing_q.z())/(sqrt(1 - (swing_q.w()*swing_q.w())));


    return v_error;
}

Eigen::Vector3d state_estimator(Quaterniond measured_q) {
    return axis_angle_error(swing_twist_decompisition(attitude_error(measured_q)));
}
